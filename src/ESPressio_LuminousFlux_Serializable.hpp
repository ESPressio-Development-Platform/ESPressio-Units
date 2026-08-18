#pragma once

#include "ESPressio_LuminousFlux.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of LuminousFlux<TValue>.
         *
         * Including ESPressio_LuminousFlux.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableLuminousFlux =
            Internal::SerializableUnitType<
                LuminousFlux<TValue>
            >;

    }

}

using namespace ESPressio::Units;
