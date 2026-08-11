#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Power : public Unit<
            TValue,
            Base,
            UnitContext::Power
        >, public Internal::UnitFactory<
            Power<TValue>,
            TValue,
            UnitContext::Power
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Power
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
