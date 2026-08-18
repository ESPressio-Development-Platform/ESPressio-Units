#pragma once

#include "ESPressio_Irradiance.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Irradiance<TValue>.
         *
         * Including ESPressio_Irradiance.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableIrradiance =
            Internal::SerializableUnitType<
                Irradiance<TValue>
            >;

    }

}

using namespace ESPressio::Units;
