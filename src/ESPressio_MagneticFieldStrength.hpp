#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MagneticFieldStrength : public Unit<
            TValue,
            Base,
            UnitContext::MagneticFieldStrength
        >, public Internal::UnitFactory<
            MagneticFieldStrength<TValue>,
            TValue,
            UnitContext::MagneticFieldStrength
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::MagneticFieldStrength
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
