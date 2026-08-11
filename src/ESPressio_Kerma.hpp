#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Kerma : public Unit<
            TValue,
            Base,
            UnitContext::Kerma
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Kerma
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
