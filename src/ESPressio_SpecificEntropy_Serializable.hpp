#pragma once

#include "ESPressio_SpecificEntropy.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of SpecificEntropy<TValue>.
         *
         * Including ESPressio_SpecificEntropy.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableSpecificEntropy =
            Internal::SerializableUnitType<
                SpecificEntropy<TValue>
            >;

    }

}

using namespace ESPressio::Units;
