#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MassConcentration : public Unit<
            TValue,
            Kilo,
            UnitContext::MassConcentration
        >, public Internal::UnitFactory<
            MassConcentration<TValue>,
            TValue,
            UnitContext::MassConcentration
        > {
            using Unit<
                TValue,
                Kilo,
                UnitContext::MassConcentration
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
