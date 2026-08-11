#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Pressure : public Unit<
            TValue,
            Base,
            UnitContext::Pressure
        >, public Internal::UnitFactory<
            Pressure<TValue>,
            TValue,
            UnitContext::Pressure
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Pressure
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
