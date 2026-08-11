#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ThermalConductivity : public Unit<
            TValue,
            Base,
            UnitContext::ThermalConductivity
        >, public Internal::UnitFactory<
            ThermalConductivity<TValue>,
            TValue,
            UnitContext::ThermalConductivity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ThermalConductivity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
