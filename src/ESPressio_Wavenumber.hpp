#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct Wavenumber : public Unit<
            TValue,
            Base,
            UnitContext::Wavenumber
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::Wavenumber
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
