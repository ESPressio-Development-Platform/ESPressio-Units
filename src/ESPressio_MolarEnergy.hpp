#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MolarEnergy : public Unit<
            TValue,
            Base,
            UnitContext::MolarEnergy
        >, public Internal::UnitFactory<
            MolarEnergy<TValue>,
            TValue,
            UnitContext::MolarEnergy
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::MolarEnergy
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
