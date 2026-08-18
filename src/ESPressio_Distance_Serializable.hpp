#pragma once

#include "ESPressio_Distance.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Distance<TValue>.
         *
         * Including ESPressio_Distance.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableDistance =
            Internal::SerializableUnitType<
                Distance<TValue>
            >;

    }

}

using namespace ESPressio::Units;
