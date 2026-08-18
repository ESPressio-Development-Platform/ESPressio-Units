#pragma once

#include "ESPressio_Power.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Power<TValue>.
         *
         * Including ESPressio_Power.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializablePower =
            Internal::SerializableUnitType<
                Power<TValue>
            >;

    }

}

using namespace ESPressio::Units;
