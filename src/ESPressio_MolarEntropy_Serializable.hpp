#pragma once

#include "ESPressio_MolarEntropy.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of MolarEntropy<TValue>.
         *
         * Including ESPressio_MolarEntropy.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableMolarEntropy =
            Internal::SerializableUnitType<
                MolarEntropy<TValue>
            >;

    }

}

using namespace ESPressio::Units;
