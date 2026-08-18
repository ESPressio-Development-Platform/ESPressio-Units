#pragma once

#include "ESPressio_ElectricChargeDensity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectricChargeDensity<TValue>.
         *
         * Including ESPressio_ElectricChargeDensity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectricChargeDensity =
            Internal::SerializableUnitType<
                ElectricChargeDensity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
