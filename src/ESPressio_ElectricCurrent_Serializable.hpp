#pragma once

#include "ESPressio_ElectricCurrent.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectricCurrent<TValue>.
         *
         * Including ESPressio_ElectricCurrent.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectricCurrent =
            Internal::SerializableUnitType<
                ElectricCurrent<TValue>
            >;

    }

}

using namespace ESPressio::Units;
