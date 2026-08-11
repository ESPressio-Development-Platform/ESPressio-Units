#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct SpecificEnergy : public Unit<
            TValue,
            Milli,
            UnitContext::SpecificEnergy
        > {
            using Unit<
                TValue,
                Milli,
                UnitContext::SpecificEnergy
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
