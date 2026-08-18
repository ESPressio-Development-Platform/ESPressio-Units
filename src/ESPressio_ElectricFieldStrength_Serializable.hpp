#pragma once

#include "ESPressio_ElectricFieldStrength.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectricFieldStrength<TValue>.
         *
         * Including ESPressio_ElectricFieldStrength.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectricFieldStrength =
            Internal::SerializableUnitType<
                ElectricFieldStrength<TValue>
            >;

    }

}

using namespace ESPressio::Units;
