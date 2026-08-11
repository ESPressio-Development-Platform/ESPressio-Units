#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MagneticFieldStrength : public Unit<
            TValue,
            Base,
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
