#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct AngularFrequency : public Unit<
            TValue,
            Base,
            UnitContext::AngularFrequency
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::AngularFrequency
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
