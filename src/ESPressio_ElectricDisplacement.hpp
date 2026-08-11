#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricDisplacement : public Unit<
            TValue,
            Base,
            UnitContext::ElectricDisplacement
        >, public Internal::UnitFactory<
            ElectricDisplacement<TValue>,
            TValue,
            UnitContext::ElectricDisplacement
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectricDisplacement
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
