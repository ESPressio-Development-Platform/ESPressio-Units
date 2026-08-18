#pragma once

#include "ESPressio_Energy.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Energy<TValue>.
         *
         * Including ESPressio_Energy.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableEnergy =
            Internal::SerializableUnitType<
                Energy<TValue>
            >;

    }

}

using namespace ESPressio::Units;
