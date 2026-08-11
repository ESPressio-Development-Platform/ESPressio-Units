#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct HeatFluxDensity : public Unit<
            TValue,
            Base,
            UnitContext::HeatFluxDensity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::HeatFluxDensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
