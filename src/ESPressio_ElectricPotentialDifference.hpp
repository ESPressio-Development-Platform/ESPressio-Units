#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricPotentialDifference : public Unit<
            TValue,
            Base,
            UnitContext::ElectricPotentialDifference
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectricPotentialDifference
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
