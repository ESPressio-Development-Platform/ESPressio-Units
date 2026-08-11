#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Illuminance : public Unit<
            TValue,
            Base,
            UnitContext::Illuminance
        >, public Internal::UnitFactory<
            Illuminance<TValue>,
            TValue,
            UnitContext::Illuminance
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Illuminance
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
