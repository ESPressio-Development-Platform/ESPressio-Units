#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MolarEntropy : public Unit<
            TValue,
            Base,
            UnitContext::MolarEntropy
        >, public Internal::UnitFactory<
            MolarEntropy<TValue>,
            TValue,
            UnitContext::MolarEntropy
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::MolarEntropy
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
