#pragma once

#include "ESPressio_Force.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Force<TValue>.
         *
         * Including ESPressio_Force.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableForce =
            Internal::SerializableUnitType<
                Force<TValue>
            >;

    }

}

using namespace ESPressio::Units;
