#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct LuminousFlux : public Unit<
            TValue,
            Base,
            UnitContext::LuminousFlux
        >, public Internal::UnitFactory<
            LuminousFlux<TValue>,
            TValue,
            UnitContext::LuminousFlux
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::LuminousFlux
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
