#pragma once

#include "ESPressio_ElectricCharge.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectricCharge<TValue>.
         *
         * Including ESPressio_ElectricCharge.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectricCharge =
            Internal::SerializableUnitType<
                ElectricCharge<TValue>
            >;

    }

}

using namespace ESPressio::Units;
