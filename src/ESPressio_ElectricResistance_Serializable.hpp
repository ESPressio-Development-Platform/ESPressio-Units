#pragma once

#include "ESPressio_ElectricResistance.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectricResistance<TValue>.
         *
         * Including ESPressio_ElectricResistance.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectricResistance =
            Internal::SerializableUnitType<
                ElectricResistance<TValue>
            >;

    }

}

using namespace ESPressio::Units;
