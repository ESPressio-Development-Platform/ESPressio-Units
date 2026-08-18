#pragma once

#include "ESPressio_HeatFluxDensity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of HeatFluxDensity<TValue>.
         *
         * Including ESPressio_HeatFluxDensity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableHeatFluxDensity =
            Internal::SerializableUnitType<
                HeatFluxDensity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
