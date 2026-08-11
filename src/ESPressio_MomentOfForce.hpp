#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MomentOfForce : public Unit<
            TValue,
            Base,
            UnitContext::MomentOfForce
        >, public Internal::UnitFactory<
            MomentOfForce<TValue>,
            TValue,
            UnitContext::MomentOfForce
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::MomentOfForce
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
