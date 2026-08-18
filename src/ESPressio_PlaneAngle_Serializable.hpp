#pragma once

#include "ESPressio_PlaneAngle.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of PlaneAngle<TValue>.
         *
         * Including ESPressio_PlaneAngle.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializablePlaneAngle =
            Internal::SerializableUnitType<
                PlaneAngle<TValue>
            >;

    }

}

using namespace ESPressio::Units;
