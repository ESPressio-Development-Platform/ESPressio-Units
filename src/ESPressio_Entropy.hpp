#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Entropy : public Unit<
            TValue,
            Base,
            UnitContext::Entropy
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Entropy
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
