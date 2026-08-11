#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct SpecificHeatCapacity : public Unit<
            TValue,
            Milli,
            UnitContext::SpecificHeatCapacity
        >, public Internal::UnitFactory<
            SpecificHeatCapacity<TValue>,
            TValue,
            UnitContext::SpecificHeatCapacity
        > {
            using Unit<
                TValue,
                Milli,
                UnitContext::SpecificHeatCapacity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
