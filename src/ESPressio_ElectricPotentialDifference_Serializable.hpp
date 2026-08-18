#pragma once

#include "ESPressio_ElectricPotentialDifference.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectricPotentialDifference<TValue>.
         *
         * Including ESPressio_ElectricPotentialDifference.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectricPotentialDifference =
            Internal::SerializableUnitType<
                ElectricPotentialDifference<TValue>
            >;

    }

}

using namespace ESPressio::Units;
