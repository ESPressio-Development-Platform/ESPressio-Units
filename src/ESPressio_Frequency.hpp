#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Frequency : public Unit<
            TValue,
            Base,
            UnitContext::Frequency
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Frequency
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
