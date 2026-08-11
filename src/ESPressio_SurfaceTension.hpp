#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct SurfaceTension : public Unit<
            TValue,
            Base,
            UnitContext::SurfaceTension
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::SurfaceTension
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
