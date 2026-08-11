#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct SolidAngle : public Unit<
            TValue,
            Base,
            UnitContext::SolidAngle
        >, public Internal::UnitFactory<
            SolidAngle<TValue>,
            TValue,
            UnitContext::SolidAngle
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::SolidAngle
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
