#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct CurrentDensity : public Unit<
            TValue,
            Base,
            UnitContext::CurrentDensity
        >, public Internal::UnitFactory<
            CurrentDensity<TValue>,
            TValue,
            UnitContext::CurrentDensity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::CurrentDensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
