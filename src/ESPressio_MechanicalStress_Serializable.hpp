#pragma once

#include "ESPressio_MechanicalStress.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of MechanicalStress<TValue>.
         *
         * Including ESPressio_MechanicalStress.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableMechanicalStress =
            Internal::SerializableUnitType<
                MechanicalStress<TValue>
            >;

    }

}

using namespace ESPressio::Units;
