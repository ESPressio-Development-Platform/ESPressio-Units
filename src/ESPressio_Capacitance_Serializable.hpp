#pragma once

#include "ESPressio_Capacitance.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Capacitance<TValue>.
         *
         * Including ESPressio_Capacitance.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableCapacitance =
            Internal::SerializableUnitType<
                Capacitance<TValue>
            >;

    }

}

using namespace ESPressio::Units;
