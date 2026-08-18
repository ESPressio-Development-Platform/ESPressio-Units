#pragma once

#include "ESPressio_Mass.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Mass<TValue>.
         *
         * Including ESPressio_Mass.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableMass =
            Internal::SerializableUnitType<
                Mass<TValue>
            >;

    }

}

using namespace ESPressio::Units;
