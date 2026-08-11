#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct CelsiusTemperature : public Unit<
            TValue,
            Base,
            UnitContext::CelsiusTemperature
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::CelsiusTemperature
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
