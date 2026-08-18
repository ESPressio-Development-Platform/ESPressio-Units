#pragma once

#include "ESPressio_HeatCapacity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of HeatCapacity<TValue>.
         *
         * Including ESPressio_HeatCapacity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableHeatCapacity =
            Internal::SerializableUnitType<
                HeatCapacity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
