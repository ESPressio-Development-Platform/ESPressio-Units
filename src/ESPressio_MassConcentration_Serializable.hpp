#pragma once

#include "ESPressio_MassConcentration.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of MassConcentration<TValue>.
         *
         * Including ESPressio_MassConcentration.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableMassConcentration =
            Internal::SerializableUnitType<
                MassConcentration<TValue>
            >;

    }

}

using namespace ESPressio::Units;
