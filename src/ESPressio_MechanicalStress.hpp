#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MechanicalStress : public Unit<
            TValue,
            Base,
            UnitContext::MechanicalStress
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::MechanicalStress
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
