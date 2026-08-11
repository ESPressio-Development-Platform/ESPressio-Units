#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Luminance : public Unit<
            TValue,
            Base,
            UnitContext::Luminance
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Luminance
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
