#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Area : public Unit<
            TValue,
            Base,
            UnitContext::Area
        >, public Internal::UnitFactory<
            Area<TValue>,
            TValue,
            UnitContext::Area
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Area
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
