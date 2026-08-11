#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricFluxDensity : public Unit<
            TValue,
            Base,
            UnitContext::ElectricFluxDensity
        >, public Internal::UnitFactory<
            ElectricFluxDensity<TValue>,
            TValue,
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
