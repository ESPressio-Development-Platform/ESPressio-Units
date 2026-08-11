#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct EnergyDensity : public Unit<
            TValue,
            Base,
            UnitContext::EnergyDensity
        >, public Internal::UnitFactory<
            EnergyDensity<TValue>,
            TValue,
            UnitContext::EnergyDensity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::EnergyDensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
