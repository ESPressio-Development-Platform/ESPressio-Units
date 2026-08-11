#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct DynamicViscosity : public Unit<
            TValue,
            Base,
            UnitContext::DynamicViscosity
        >, public Internal::UnitFactory<
            DynamicViscosity<TValue>,
            TValue,
            UnitContext::DynamicViscosity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::DynamicViscosity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
