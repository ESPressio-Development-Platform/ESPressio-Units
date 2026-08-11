#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct SpecificVolume : public Unit<
            TValue,
            Milli,
            UnitContext::SpecificVolume
        > {
            using Unit<
                TValue,
                Milli,
                UnitContext::SpecificVolume
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
