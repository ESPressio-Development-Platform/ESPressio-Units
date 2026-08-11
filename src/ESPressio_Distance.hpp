#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Distance : public Unit<
            TValue,
            Base,
            UnitContext::Distance
        >, public Internal::UnitFactory<
            Distance<TValue>,
            TValue,
            UnitContext::Distance
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Distance
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
