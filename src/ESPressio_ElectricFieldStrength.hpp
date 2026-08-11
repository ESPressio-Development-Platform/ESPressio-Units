#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricFieldStrength : public Unit<
            TValue,
            Base,
            UnitContext::ElectricFieldStrength
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectricFieldStrength
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
