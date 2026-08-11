#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Work : public Unit<
            TValue,
            Base,
            UnitContext::Work
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Work
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
