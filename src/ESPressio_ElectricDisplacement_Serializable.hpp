#pragma once

#include "ESPressio_ElectricDisplacement.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectricDisplacement<TValue>.
         *
         * Including ESPressio_ElectricDisplacement.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectricDisplacement =
            Internal::SerializableUnitType<
                ElectricDisplacement<TValue>
            >;

    }

}

using namespace ESPressio::Units;
