#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Permittivity : public Unit<
            TValue,
            Base,
            UnitContext::Permittivity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Permittivity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
