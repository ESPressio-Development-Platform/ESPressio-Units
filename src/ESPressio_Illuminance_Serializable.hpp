#pragma once

#include "ESPressio_Illuminance.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Illuminance<TValue>.
         *
         * Including ESPressio_Illuminance.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableIlluminance =
            Internal::SerializableUnitType<
                Illuminance<TValue>
            >;

    }

}

using namespace ESPressio::Units;
