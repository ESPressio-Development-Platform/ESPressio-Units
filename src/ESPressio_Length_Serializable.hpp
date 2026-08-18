#pragma once

#include "ESPressio_Length.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Length<TValue>.
         *
         * Including ESPressio_Length.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableLength =
            Internal::SerializableUnitType<
                Length<TValue>
            >;

    }

}

using namespace ESPressio::Units;
