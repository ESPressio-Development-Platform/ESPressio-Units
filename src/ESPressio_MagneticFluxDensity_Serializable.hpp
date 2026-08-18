#pragma once

#include "ESPressio_MagneticFluxDensity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of MagneticFluxDensity<TValue>.
         *
         * Including ESPressio_MagneticFluxDensity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableMagneticFluxDensity =
            Internal::SerializableUnitType<
                MagneticFluxDensity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
