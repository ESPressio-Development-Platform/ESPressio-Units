#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MagneticFlux : public Unit<
            TValue,
            Base,
            UnitContext::MagneticFlux
        >, public Internal::UnitFactory<
            MagneticFlux<TValue>,
            TValue,
            UnitContext::MagneticFlux
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::MagneticFlux
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
