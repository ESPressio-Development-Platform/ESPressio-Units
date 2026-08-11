#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricCurrent : public Unit<
            TValue,
            Base,
            UnitContext::ElectricCurrent
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectricCurrent
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
