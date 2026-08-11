#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct SurfaceChargeDensity : public Unit<
            TValue,
            Base,
            UnitContext::SurfaceChargeDensity
        >, public Internal::UnitFactory<
            SurfaceChargeDensity<TValue>,
            TValue,
            UnitContext::SurfaceChargeDensity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::SurfaceChargeDensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
