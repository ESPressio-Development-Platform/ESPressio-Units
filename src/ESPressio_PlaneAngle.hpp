#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct PlaneAngle : public Unit<
            TValue,
            Base,
            UnitContext::PlaneAngle
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::PlaneAngle
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
