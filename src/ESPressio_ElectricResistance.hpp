#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricResistance : public Unit<
            TValue,
            Base,
            UnitContext::ElectricResistance
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectricResistance
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
