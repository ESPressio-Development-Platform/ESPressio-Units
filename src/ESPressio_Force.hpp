#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Force : public Unit<
            TValue,
            Base,
            UnitContext::Force
        >, public Internal::UnitFactory<
            Force<TValue>,
            TValue,
            UnitContext::Force
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Force
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
