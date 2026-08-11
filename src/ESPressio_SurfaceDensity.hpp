#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct SurfaceDensity : public Unit<
            TValue,
            Kilo,
            UnitContext::SurfaceDensity
        >, public Internal::UnitFactory<
            SurfaceDensity<TValue>,
            TValue,
            UnitContext::SurfaceDensity
        > {
            using Unit<
                TValue,
                Kilo,
                UnitContext::SurfaceDensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
