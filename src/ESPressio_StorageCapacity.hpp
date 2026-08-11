#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct StorageCapacity : public Unit<
            TValue,
            Base,
            UnitContext::StorageCapacity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::StorageCapacity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
