#pragma once

#include "ESPressio_Dimensionless.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Dimensionless<TValue>.
         *
         * Including ESPressio_Dimensionless.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableDimensionless =
            Internal::SerializableUnitType<
                Dimensionless<TValue>
            >;

    }

}

using namespace ESPressio::Units;
