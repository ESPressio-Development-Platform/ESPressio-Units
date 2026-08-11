#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct LuminousIntensity : public Unit<
            TValue,
            Base,
            UnitContext::LuminousIntensity
        >, public Internal::UnitFactory<
            LuminousIntensity<TValue>,
            TValue,
            UnitContext::LuminousIntensity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::LuminousIntensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
