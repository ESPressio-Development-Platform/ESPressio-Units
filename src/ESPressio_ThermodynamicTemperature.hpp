#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ThermodynamicTemperature : public Unit<
            TValue,
            Base,
            UnitContext::ThermodynamicTemperature
        >, public Internal::UnitFactory<
            ThermodynamicTemperature<TValue>,
            TValue,
            UnitContext::ThermodynamicTemperature
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ThermodynamicTemperature
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
