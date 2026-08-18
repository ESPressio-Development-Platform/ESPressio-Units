#pragma once

#include "ESPressio_LuminousIntensity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of LuminousIntensity<TValue>.
         *
         * Including ESPressio_LuminousIntensity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableLuminousIntensity =
            Internal::SerializableUnitType<
                LuminousIntensity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
