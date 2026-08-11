#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricPotential : public Unit<
            TValue,
            Base,
            UnitContext::ElectricPotential
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectricPotential
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
