#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Velocity : public Unit<
            TValue,
            Base,
            UnitContext::Velocity
        >, public Internal::UnitFactory<
            Velocity<TValue>,
            TValue,
            UnitContext::Velocity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Velocity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
