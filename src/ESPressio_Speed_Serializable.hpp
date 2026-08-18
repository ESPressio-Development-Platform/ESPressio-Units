#pragma once

#include "ESPressio_Speed.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Speed<TValue>.
         *
         * Including ESPressio_Speed.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableSpeed =
            Internal::SerializableUnitType<
                Speed<TValue>
            >;

    }

}

using namespace ESPressio::Units;
