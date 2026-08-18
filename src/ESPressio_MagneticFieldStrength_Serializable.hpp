#pragma once

#include "ESPressio_MagneticFieldStrength.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of MagneticFieldStrength<TValue>.
         *
         * Including ESPressio_MagneticFieldStrength.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableMagneticFieldStrength =
            Internal::SerializableUnitType<
                MagneticFieldStrength<TValue>
            >;

    }

}

using namespace ESPressio::Units;
