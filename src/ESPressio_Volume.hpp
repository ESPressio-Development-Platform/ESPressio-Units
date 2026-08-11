#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Volume : public Unit<
            TValue,
            Base,
            UnitContext::Volume
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Volume
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
