#pragma once

#include "ESPressio_Ratio.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Ratio<TValue>.
         *
         * Including ESPressio_Ratio.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableRatio =
            Internal::SerializableUnitType<
                Ratio<TValue>
            >;

    }

}

using namespace ESPressio::Units;
