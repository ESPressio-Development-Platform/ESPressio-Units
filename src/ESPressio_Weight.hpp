#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Weight : public Unit<
            TValue,
            Base,
            UnitContext::Weight
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Weight
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
