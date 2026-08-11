#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Inductance : public Unit<
            TValue,
            Base,
            UnitContext::Inductance
        >, public Internal::UnitFactory<
            Inductance<TValue>,
            TValue,
            UnitContext::Inductance
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Inductance
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
