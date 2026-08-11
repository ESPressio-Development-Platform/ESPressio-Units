#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct DoseEquivalent : public Unit<
            TValue,
            Base,
            UnitContext::DoseEquivalent
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::DoseEquivalent
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
