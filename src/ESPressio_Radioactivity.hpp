#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Radioactivity : public Unit<
            TValue,
            Base,
            UnitContext::Radioactivity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Radioactivity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
