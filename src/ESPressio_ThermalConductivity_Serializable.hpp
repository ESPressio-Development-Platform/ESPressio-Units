#pragma once

#include "ESPressio_ThermalConductivity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ThermalConductivity<TValue>.
         *
         * Including ESPressio_ThermalConductivity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableThermalConductivity =
            Internal::SerializableUnitType<
                ThermalConductivity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
