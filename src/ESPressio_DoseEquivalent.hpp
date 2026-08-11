#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct DoseEquivalent : public Unit<
            TValue,
            Base,
            UnitContext::DoseEquivalent
        >, public Internal::UnitFactory<
            DoseEquivalent<TValue>,
            TValue,
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
