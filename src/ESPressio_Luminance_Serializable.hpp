#pragma once

#include "ESPressio_Luminance.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Luminance<TValue>.
         *
         * Including ESPressio_Luminance.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableLuminance =
            Internal::SerializableUnitType<
                Luminance<TValue>
            >;

    }

}

using namespace ESPressio::Units;
