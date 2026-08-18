#pragma once

#include "ESPressio_Inductance.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Inductance<TValue>.
         *
         * Including ESPressio_Inductance.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableInductance =
            Internal::SerializableUnitType<
                Inductance<TValue>
            >;

    }

}

using namespace ESPressio::Units;
