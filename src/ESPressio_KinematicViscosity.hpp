#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct KinematicViscosity : public Unit<
            TValue,
            Base,
            UnitContext::KinematicViscosity
        >, public Internal::UnitFactory<
            KinematicViscosity<TValue>,
            TValue,
            UnitContext::KinematicViscosity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::KinematicViscosity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
