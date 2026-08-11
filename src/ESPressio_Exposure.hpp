#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Exposure : public Unit<
            TValue,
            Milli,
            UnitContext::Exposure
        >, public Internal::UnitFactory<
            Exposure<TValue>,
            TValue,
            UnitContext::Exposure
        > {
            using Unit<
                TValue,
                Milli,
                UnitContext::Exposure
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
