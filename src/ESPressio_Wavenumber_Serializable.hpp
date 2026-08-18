#pragma once

#include "ESPressio_Wavenumber.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Wavenumber<TValue>.
         *
         * Including ESPressio_Wavenumber.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableWavenumber =
            Internal::SerializableUnitType<
                Wavenumber<TValue>
            >;

    }

}

using namespace ESPressio::Units;
