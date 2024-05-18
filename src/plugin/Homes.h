#include "RBStream.h"
#include "mc/math/Vec3.h"
#include <string>

struct Vec4 {
    Vec3 vc;
    char dimid;

    std::string toStr() const {
        return "(" + std::to_string(vc.x) + " , " + std::to_string(vc.y) + " , " + std::to_string(vc.z) + " , "
             + std::to_string(dimid) + " , " + ")";
    }

    template <typename _TP>
    void pack(WBStreamImpl<_TP>& ws) const {
        ws.apply(vc.x, vc.y, vc.z, dimid);
    }

    void unpack(RBStream& rs) { rs.apply(vc.x, vc.y, vc.z, dimid); }

    Vec4(Vec3 x, int dim) : vc(x), dimid(dim) {}

    Vec4() {}
};

struct Homes {
    struct Home {
        Vec4        pos;
        std::string name;

        template <typename _TP>
        void pack(WBStreamImpl<_TP>& ws) const {
            ws.apply(pos, name);
        }

        void unpack(RBStream& rs) { rs.apply(pos, name); }
    };
    std::list<Home> data;

    template <typename _TP>
    void pack(WBStreamImpl<_TP>& ws) const {
        ws.apply(data);
    }

    void unpack(RBStream& rs) { rs.apply(data); }
};
