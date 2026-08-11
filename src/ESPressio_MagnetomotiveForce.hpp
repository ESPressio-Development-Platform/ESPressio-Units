#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct MagnetomotiveForce : public Unit<
            TValue,
            Base,
            UnitContext::MagnetomotiveForce
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::MagnetomotiveForce
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
