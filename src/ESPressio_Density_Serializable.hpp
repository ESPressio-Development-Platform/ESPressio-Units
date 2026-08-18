#pragma once

#include "ESPressio_Density.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Density<TValue>.
         *
         * Including ESPressio_Density.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableDensity =
            Internal::SerializableUnitType<
                Density<TValue>
            >;

    }

}

using namespace ESPressio::Units;
