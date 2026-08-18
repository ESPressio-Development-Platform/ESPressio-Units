#pragma once

#include "ESPressio_ThermodynamicTemperature.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ThermodynamicTemperature<TValue>.
         *
         * Including ESPressio_ThermodynamicTemperature.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableThermodynamicTemperature =
            Internal::SerializableUnitType<
                ThermodynamicTemperature<TValue>
            >;

    }

}

using namespace ESPressio::Units;
