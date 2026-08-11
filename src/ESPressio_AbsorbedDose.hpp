#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct AbsorbedDose : public Unit<
            TValue,
            Base,
            UnitContext::AbsorbedDose
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::AbsorbedDose
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
