#pragma once

#include "ESPressio_Torque.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Torque<TValue>.
         *
         * Including ESPressio_Torque.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableTorque =
            Internal::SerializableUnitType<
                Torque<TValue>
            >;

    }

}

using namespace ESPressio::Units;
