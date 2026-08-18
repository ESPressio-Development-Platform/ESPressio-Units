#pragma once

#include "ESPressio_Entropy.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Entropy<TValue>.
         *
         * Including ESPressio_Entropy.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableEntropy =
            Internal::SerializableUnitType<
                Entropy<TValue>
            >;

    }

}

using namespace ESPressio::Units;
