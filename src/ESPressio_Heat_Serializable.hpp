#pragma once

#include "ESPressio_Heat.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Heat<TValue>.
         *
         * Including ESPressio_Heat.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableHeat =
            Internal::SerializableUnitType<
                Heat<TValue>
            >;

    }

}

using namespace ESPressio::Units;
