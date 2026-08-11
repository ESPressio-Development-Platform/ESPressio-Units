#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Irradiance : public Unit<
            TValue,
            Base,
            UnitContext::Irradiance
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Irradiance
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
