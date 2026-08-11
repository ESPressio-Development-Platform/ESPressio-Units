#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MolarEntropy : public Unit<
            TValue,
            Base,
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
