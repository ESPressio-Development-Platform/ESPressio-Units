#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MagneticFluxDensity : public Unit<
            TValue,
            Base,
            UnitContext::MagneticFluxDensity
        >, public Internal::UnitFactory<
            MagneticFluxDensity<TValue>,
            TValue,
            UnitContext::MagneticFluxDensity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::MagneticFluxDensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
