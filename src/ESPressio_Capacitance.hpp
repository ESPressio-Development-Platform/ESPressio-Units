#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Capacitance : public Unit<
            TValue,
            Base,
            UnitContext::Capacitance
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Capacitance
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
