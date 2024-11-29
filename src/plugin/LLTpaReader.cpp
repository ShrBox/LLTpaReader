#include "plugin/LLTpaReader.h"

#include <memory>
#include <string>
#include <unordered_map>
#include "Homes.h"
#include "ll/api/data/KeyValueDB.h"
#include "ll/api/io/FileUtils.h"
#include "ll/api/mod/RegisterHelper.h"
#include "nlohmann/json.hpp"

namespace lltpa_reader {

static std::unique_ptr<LLTpaReader> instance;

LLTpaReader& LLTpaReader::getInstance() { return *instance; }

bool LLTpaReader::load() {
    getSelf().getLogger().info("Loading...");
    ll::data::KeyValueDB db(getSelf().getDataDir());
    nlohmann::json       json;
    db.iter([&](std::string_view key, std::string_view value) {
        unsigned long long ull;
        std::string        xuid;
        if (key.size() == sizeof(unsigned long long)) {
            std::memcpy(&ull, key.data(), sizeof(unsigned long long));
            xuid = std::to_string(ull);
        } else {
            return true;
        }
        Homes    homes;
        RBStream stream(value);
        homes.unpack(stream);
        for (auto& home : homes.data) {
            json["homes"][xuid][home.name] = {
                {"x",         home.pos.vc.x },
                {"y",         home.pos.vc.y },
                {"z",         home.pos.vc.z },
                {"dimension", home.pos.dimid}
            };
        }
        return true;
    });

    std::unordered_map<std::string, Vec4> warps;
    auto                                  warpsStr = db.get("warps");
    if (warpsStr.has_value()) {
        RBStream stream(warpsStr.value());
        stream.apply(warps);
        for (auto& i : warps) {
            json["warps"][i.first] = {
                {"x",         i.second.vc.x },
                {"y",         i.second.vc.y },
                {"z",         i.second.vc.z },
                {"dimension", i.second.dimid}
            };
        }
    }
    ll::file_utils::writeFile(getSelf().getModDir() / "output.json", json.dump(4));
    getSelf().getLogger().warn("Tpa data has been exported in plugins/LLTpaReader/output.json");
    return true;
}

bool LLTpaReader::enable() { return true; }

bool LLTpaReader::disable() { return true; }

} // namespace lltpa_reader

LL_REGISTER_MOD(lltpa_reader::LLTpaReader, lltpa_reader::instance);
