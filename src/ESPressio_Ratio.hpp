#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Ratio : public Unit<
            TValue,
            Base,
            UnitContext::Ratio
        >, public Internal::UnitFactory<
            Ratio<TValue>,
            TValue,
            UnitContext::Ratio
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Ratio
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
