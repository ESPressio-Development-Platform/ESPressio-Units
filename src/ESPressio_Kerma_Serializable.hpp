#pragma once

#include "ESPressio_Kerma.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Kerma<TValue>.
         *
         * Including ESPressio_Kerma.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableKerma =
            Internal::SerializableUnitType<
                Kerma<TValue>
            >;

    }

}

using namespace ESPressio::Units;
