#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectricCharge : public Unit<
            TValue,
            Base,
            UnitContext::ElectricCharge
        >, public Internal::UnitFactory<
            ElectricCharge<TValue>,
            TValue,
            UnitContext::ElectricCharge
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectricCharge
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
