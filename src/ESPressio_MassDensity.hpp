#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MassDensity : public Unit<
            TValue,
            Kilo,
            UnitContext::MassDensity
        > {
            using Unit<
                TValue,
                Kilo,
                UnitContext::MassDensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
