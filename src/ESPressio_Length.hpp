#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Length : public Unit<
            TValue,
            Base,
            UnitContext::Length
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Length
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
