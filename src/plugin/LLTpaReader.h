#pragma once

#include "ll/api/mod//NativeMod.h"

namespace lltpa_reader {

class LLTpaReader {

public:
    static LLTpaReader& getInstance();

    LLTpaReader(ll::mod::NativeMod& self) : mSelf(self) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();

private:
    ll::mod::NativeMod& mSelf;
};

} // namespace lltpa_reader
