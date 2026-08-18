#pragma once

#include "ESPressio_ElectricFluxDensity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectricFluxDensity<TValue>.
         *
         * Including ESPressio_ElectricFluxDensity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectricFluxDensity =
            Internal::SerializableUnitType<
                ElectricFluxDensity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
