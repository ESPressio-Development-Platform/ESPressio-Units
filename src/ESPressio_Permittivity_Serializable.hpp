#pragma once

#include "ESPressio_Permittivity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Permittivity<TValue>.
         *
         * Including ESPressio_Permittivity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializablePermittivity =
            Internal::SerializableUnitType<
                Permittivity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
