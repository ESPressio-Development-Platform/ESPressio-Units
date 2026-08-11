#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct SpecificEntropy : public Unit<
            TValue,
            Milli,
            UnitContext::SpecificEntropy
        >, public Internal::UnitFactory<
            SpecificEntropy<TValue>,
            TValue,
            UnitContext::SpecificEntropy
        > {
            using Unit<
                TValue,
                Milli,
                UnitContext::SpecificEntropy
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
