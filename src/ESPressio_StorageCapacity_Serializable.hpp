#pragma once

#include "ESPressio_StorageCapacity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of StorageCapacity<TValue>.
         *
         * Including ESPressio_StorageCapacity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableStorageCapacity =
            Internal::SerializableUnitType<
                StorageCapacity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
