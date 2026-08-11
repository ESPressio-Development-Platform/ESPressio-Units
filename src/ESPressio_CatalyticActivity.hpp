#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <typename TValue>
        struct CatalyticActivity : public Unit<
            TValue,
            Base,
            UnitContext::CatalyticActivity
        >, public Internal::UnitFactory<
            CatalyticActivity<TValue>,
            TValue,
            UnitContext::CatalyticActivity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::CatalyticActivity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
