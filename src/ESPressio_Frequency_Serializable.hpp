#pragma once

#include "ESPressio_Frequency.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Frequency<TValue>.
         *
         * Including ESPressio_Frequency.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableFrequency =
            Internal::SerializableUnitType<
                Frequency<TValue>
            >;

    }

}

using namespace ESPressio::Units;
