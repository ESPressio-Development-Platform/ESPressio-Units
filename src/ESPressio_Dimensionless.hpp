#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Dimensionless : public Unit<
            TValue,
            Base,
            UnitContext::Dimensionless
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Dimensionless
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
