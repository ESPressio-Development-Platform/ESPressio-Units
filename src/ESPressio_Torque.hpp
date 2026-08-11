#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Torque : public Unit<
            TValue,
            Base,
            UnitContext::Torque
        >, public Internal::UnitFactory<
            Torque<TValue>,
            TValue,
            UnitContext::Torque
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Torque
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
