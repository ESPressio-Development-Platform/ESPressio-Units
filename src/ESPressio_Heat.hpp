#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Heat : public Unit<
            TValue,
            Base,
            UnitContext::Heat
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Heat
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
