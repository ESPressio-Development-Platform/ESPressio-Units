#pragma once

#include "ESPressio_ElectricPotential.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectricPotential<TValue>.
         *
         * Including ESPressio_ElectricPotential.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectricPotential =
            Internal::SerializableUnitType<
                ElectricPotential<TValue>
            >;

    }

}

using namespace ESPressio::Units;
