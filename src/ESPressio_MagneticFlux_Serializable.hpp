#pragma once

#include "ESPressio_MagneticFlux.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of MagneticFlux<TValue>.
         *
         * Including ESPressio_MagneticFlux.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableMagneticFlux =
            Internal::SerializableUnitType<
                MagneticFlux<TValue>
            >;

    }

}

using namespace ESPressio::Units;
