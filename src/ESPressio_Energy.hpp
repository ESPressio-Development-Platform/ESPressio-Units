#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Energy : public Unit<
            TValue,
            Base,
            UnitContext::Energy
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Energy
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
