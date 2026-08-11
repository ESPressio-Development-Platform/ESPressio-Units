#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Density : public Unit<
            TValue,
            Kilo,
            UnitContext::Density
        > {
            using Unit<
                TValue,
                Kilo,
                UnitContext::Density
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
