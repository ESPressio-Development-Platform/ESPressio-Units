#pragma once

#include "ESPressio_SpecificHeatCapacity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of SpecificHeatCapacity<TValue>.
         *
         * Including ESPressio_SpecificHeatCapacity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableSpecificHeatCapacity =
            Internal::SerializableUnitType<
                SpecificHeatCapacity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
