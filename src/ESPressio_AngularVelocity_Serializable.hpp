#pragma once

#include "ESPressio_AngularVelocity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of AngularVelocity<TValue>.
         *
         * Including ESPressio_AngularVelocity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableAngularVelocity =
            Internal::SerializableUnitType<
                AngularVelocity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
