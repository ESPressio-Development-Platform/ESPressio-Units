#pragma once

#include "ESPressio_AngularAcceleration.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of AngularAcceleration<TValue>.
         *
         * Including ESPressio_AngularAcceleration.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableAngularAcceleration =
            Internal::SerializableUnitType<
                AngularAcceleration<TValue>
            >;

    }

}

using namespace ESPressio::Units;
