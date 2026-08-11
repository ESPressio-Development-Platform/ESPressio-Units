#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Time : public Unit<
            TValue,
            Base,
            UnitContext::Time
        >, public Internal::UnitFactory<
            Time<TValue>,
            TValue,
            UnitContext::Time
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Time
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
