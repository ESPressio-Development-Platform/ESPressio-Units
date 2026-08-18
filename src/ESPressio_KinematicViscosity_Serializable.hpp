#pragma once

#include "ESPressio_KinematicViscosity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of KinematicViscosity<TValue>.
         *
         * Including ESPressio_KinematicViscosity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableKinematicViscosity =
            Internal::SerializableUnitType<
                KinematicViscosity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
