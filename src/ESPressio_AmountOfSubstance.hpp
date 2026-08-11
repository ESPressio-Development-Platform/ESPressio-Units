#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct AmountOfSubstance : public Unit<
            TValue,
            Base,
            UnitContext::AmountOfSubstance
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::AmountOfSubstance
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
