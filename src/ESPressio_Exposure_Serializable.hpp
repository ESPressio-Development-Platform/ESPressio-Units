#pragma once

#include "ESPressio_Exposure.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Exposure<TValue>.
         *
         * Including ESPressio_Exposure.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableExposure =
            Internal::SerializableUnitType<
                Exposure<TValue>
            >;

    }

}

using namespace ESPressio::Units;
