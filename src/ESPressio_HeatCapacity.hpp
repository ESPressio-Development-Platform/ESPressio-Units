#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct HeatCapacity : public Unit<
            TValue,
            Base,
            UnitContext::HeatCapacity
        >, public Internal::UnitFactory<
            HeatCapacity<TValue>,
            TValue,
            UnitContext::HeatCapacity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::HeatCapacity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
