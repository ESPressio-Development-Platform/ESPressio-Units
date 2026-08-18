#pragma once

#include "ESPressio_SpecificEnergy.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of SpecificEnergy<TValue>.
         *
         * Including ESPressio_SpecificEnergy.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableSpecificEnergy =
            Internal::SerializableUnitType<
                SpecificEnergy<TValue>
            >;

    }

}

using namespace ESPressio::Units;
