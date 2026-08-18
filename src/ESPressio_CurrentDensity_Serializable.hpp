#pragma once

#include "ESPressio_CurrentDensity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of CurrentDensity<TValue>.
         *
         * Including ESPressio_CurrentDensity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableCurrentDensity =
            Internal::SerializableUnitType<
                CurrentDensity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
