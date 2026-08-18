#pragma once

#include "ESPressio_Pressure.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Pressure<TValue>.
         *
         * Including ESPressio_Pressure.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializablePressure =
            Internal::SerializableUnitType<
                Pressure<TValue>
            >;

    }

}

using namespace ESPressio::Units;
