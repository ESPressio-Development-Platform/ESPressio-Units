#pragma once

#include "ESPressio_MassDensity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of MassDensity<TValue>.
         *
         * Including ESPressio_MassDensity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableMassDensity =
            Internal::SerializableUnitType<
                MassDensity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
