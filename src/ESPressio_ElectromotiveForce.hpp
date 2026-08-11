#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct ElectromotiveForce : public Unit<
            TValue,
            Base,
            UnitContext::ElectromotiveForce
        >, public Internal::UnitFactory<
            ElectromotiveForce<TValue>,
            TValue,
            UnitContext::ElectromotiveForce
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::ElectromotiveForce
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
