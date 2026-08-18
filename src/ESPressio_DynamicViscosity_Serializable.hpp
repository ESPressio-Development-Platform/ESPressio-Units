#pragma once

#include "ESPressio_DynamicViscosity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of DynamicViscosity<TValue>.
         *
         * Including ESPressio_DynamicViscosity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableDynamicViscosity =
            Internal::SerializableUnitType<
                DynamicViscosity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
