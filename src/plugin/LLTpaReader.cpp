#include "plugin/LLTpaReader.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <unordered_map>

#include "Homes.h"
#include "ll/api/data/KeyValueDB.h"
#include "ll/api/plugin/NativePlugin.h"
#include "ll/api/plugin/Plugin.h"
#include "ll/api/plugin/RegisterHelper.h"


namespace lltpa_reader {

static std::unique_ptr<LLTpaReader> instance;

LLTpaReader& LLTpaReader::getInstance() { return *instance; }

bool LLTpaReader::load() {
    getSelf().getLogger().info("Loading...");
    ll::data::KeyValueDB db(getSelf().getDataDir());
    db.iter([&](std::string_view key, std::string_view value) {
        unsigned long long ull;
        if (key.size() == sizeof(unsigned long long)) {
            std::memcpy(&ull, key.data(), sizeof(unsigned long long));
        } else {
            return true;
        }
        getSelf().getLogger().info("{}", ull);
        Homes    homes;
        RBStream stream(value);
        homes.unpack(stream);
        for (Homes::Home& home : homes.data) {
            getSelf().getLogger().info("{} {}", home.name, home.pos.toStr());
        }
        return true;
    });
    std::unordered_map<std::string, Vec4> warps;
    auto                                  warpsStr = db.get("warps");
    if (warpsStr.has_value()) {
        RBStream stream(warpsStr.value());
        stream.apply(warps);
    }
    for (auto& warp : warps) {
        getSelf().getLogger().info("{} {}", warp.first, warp.second.toStr());
    }
    // Code for loading the plugin goes here.
    return true;
}

bool LLTpaReader::enable() {
    getSelf().getLogger().info("Enabling...");
    // Code for enabling the plugin goes here.
    return true;
}

bool LLTpaReader::disable() {
    getSelf().getLogger().info("Disabling...");
    // Code for disabling the plugin goes here.
    return true;
}

} // namespace lltpa_reader

LL_REGISTER_PLUGIN(lltpa_reader::LLTpaReader, lltpa_reader::instance);
