#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Permeability : public Unit<
            TValue,
            Base,
            UnitContext::Permeability
        >, public Internal::UnitFactory<
            Permeability<TValue>,
            TValue,
            UnitContext::Permeability
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Permeability
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
