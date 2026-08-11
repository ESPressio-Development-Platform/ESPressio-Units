#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricConductance : public Unit<
            TValue,
            Base,
            UnitContext::ElectricConductance
        >, public Internal::UnitFactory<
            ElectricConductance<TValue>,
            TValue,
            UnitContext::ElectricConductance
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectricConductance
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
