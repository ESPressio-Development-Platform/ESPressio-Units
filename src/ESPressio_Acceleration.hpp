#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Acceleration : public Unit<
            TValue,
            Base,
            UnitContext::Acceleration
        >, public Internal::UnitFactory<
            Acceleration<TValue>,
            TValue,
            UnitContext::Acceleration
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Acceleration
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
