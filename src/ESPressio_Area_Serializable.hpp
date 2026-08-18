#pragma once

#include "ESPressio_Area.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Area<TValue>.
         *
         * Including ESPressio_Area.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableArea =
            Internal::SerializableUnitType<
                Area<TValue>
            >;

    }

}

using namespace ESPressio::Units;
