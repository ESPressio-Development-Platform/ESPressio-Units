#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Mass : public Unit<
            TValue,
            Kilo,
            UnitContext::Mass
        >, public Internal::UnitFactory<
            Mass<TValue>,
            TValue,
            UnitContext::Mass
        > {
            using Unit<
                TValue,
                Kilo,
                UnitContext::Mass
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
