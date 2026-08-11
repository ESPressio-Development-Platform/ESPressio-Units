#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricFluxDensity : public Unit<
            TValue,
            Base,
            UnitContext::ElectricFluxDensity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectricFluxDensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
