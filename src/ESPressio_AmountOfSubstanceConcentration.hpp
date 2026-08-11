#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct AmountOfSubstanceConcentration : public Unit<
            TValue,
            Base,
            UnitContext::AmountOfSubstanceConcentration
        >, public Internal::UnitFactory<
            AmountOfSubstanceConcentration<TValue>,
            TValue,
            UnitContext::AmountOfSubstanceConcentration
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::AmountOfSubstanceConcentration
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
