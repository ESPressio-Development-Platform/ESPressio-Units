#pragma once

#include "ESPressio_ElectricConductance.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectricConductance<TValue>.
         *
         * Including ESPressio_ElectricConductance.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectricConductance =
            Internal::SerializableUnitType<
                ElectricConductance<TValue>
            >;

    }

}

using namespace ESPressio::Units;
