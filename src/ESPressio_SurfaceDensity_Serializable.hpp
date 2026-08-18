#pragma once

#include "ESPressio_SurfaceDensity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of SurfaceDensity<TValue>.
         *
         * Including ESPressio_SurfaceDensity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableSurfaceDensity =
            Internal::SerializableUnitType<
                SurfaceDensity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
