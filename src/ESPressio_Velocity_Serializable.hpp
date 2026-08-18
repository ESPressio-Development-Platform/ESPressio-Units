#pragma once

#include "ESPressio_Velocity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Velocity<TValue>.
         *
         * Including ESPressio_Velocity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableVelocity =
            Internal::SerializableUnitType<
                Velocity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
