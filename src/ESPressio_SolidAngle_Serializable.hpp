#pragma once

#include "ESPressio_SolidAngle.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of SolidAngle<TValue>.
         *
         * Including ESPressio_SolidAngle.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableSolidAngle =
            Internal::SerializableUnitType<
                SolidAngle<TValue>
            >;

    }

}

using namespace ESPressio::Units;
