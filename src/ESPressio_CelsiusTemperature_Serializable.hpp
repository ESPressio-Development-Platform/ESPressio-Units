#pragma once

#include "ESPressio_CelsiusTemperature.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of CelsiusTemperature<TValue>.
         *
         * Including ESPressio_CelsiusTemperature.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableCelsiusTemperature =
            Internal::SerializableUnitType<
                CelsiusTemperature<TValue>
            >;

    }

}

using namespace ESPressio::Units;
