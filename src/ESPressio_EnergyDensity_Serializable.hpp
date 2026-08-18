#pragma once

#include "ESPressio_EnergyDensity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of EnergyDensity<TValue>.
         *
         * Including ESPressio_EnergyDensity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableEnergyDensity =
            Internal::SerializableUnitType<
                EnergyDensity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
