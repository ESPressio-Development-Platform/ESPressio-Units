#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct AngularVelocity : public Unit<
            TValue,
            Base,
            UnitContext::AngularVelocity
        >, public Internal::UnitFactory<
            AngularVelocity<TValue>,
            TValue,
            UnitContext::AngularVelocity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::AngularVelocity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
