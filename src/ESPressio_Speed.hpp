#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Speed : public Unit<
            TValue,
            Base,
            UnitContext::Speed
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Speed
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
