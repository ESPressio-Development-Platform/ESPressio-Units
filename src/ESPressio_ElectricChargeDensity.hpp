#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricChargeDensity : public Unit<
            TValue,
            Base,
            UnitContext::ElectricChargeDensity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectricChargeDensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
