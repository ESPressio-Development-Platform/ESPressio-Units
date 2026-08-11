#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct AmountOfSubstance : public Unit<
            TValue,
            Base,
            UnitContext::AmountOfSubstance
        >, public Internal::UnitFactory<
            AmountOfSubstance<TValue>,
            TValue,
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
