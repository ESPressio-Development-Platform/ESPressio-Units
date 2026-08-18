#pragma once

#include "ESPressio_Weight.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Weight<TValue>.
         *
         * Including ESPressio_Weight.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableWeight =
            Internal::SerializableUnitType<
                Weight<TValue>
            >;

    }

}

using namespace ESPressio::Units;
