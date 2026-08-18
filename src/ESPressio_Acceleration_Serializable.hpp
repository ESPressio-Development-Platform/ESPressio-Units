#pragma once

#include "ESPressio_Acceleration.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Acceleration<TValue>.
         *
         * Including ESPressio_Acceleration.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableAcceleration =
            Internal::SerializableUnitType<
                Acceleration<TValue>
            >;

    }

}

using namespace ESPressio::Units;
