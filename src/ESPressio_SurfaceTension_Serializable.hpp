#pragma once

#include "ESPressio_SurfaceTension.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of SurfaceTension<TValue>.
         *
         * Including ESPressio_SurfaceTension.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableSurfaceTension =
            Internal::SerializableUnitType<
                SurfaceTension<TValue>
            >;

    }

}

using namespace ESPressio::Units;
