#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct AngularAcceleration : public Unit<
            TValue,
            Base,
            UnitContext::AngularAcceleration
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::AngularAcceleration
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
