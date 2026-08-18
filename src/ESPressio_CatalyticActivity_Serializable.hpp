#pragma once

#include "ESPressio_CatalyticActivity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of CatalyticActivity<TValue>.
         *
         * Including ESPressio_CatalyticActivity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableCatalyticActivity =
            Internal::SerializableUnitType<
                CatalyticActivity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
