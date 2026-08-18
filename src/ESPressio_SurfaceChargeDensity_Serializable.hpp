#pragma once

#include "ESPressio_SurfaceChargeDensity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of SurfaceChargeDensity<TValue>.
         *
         * Including ESPressio_SurfaceChargeDensity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableSurfaceChargeDensity =
            Internal::SerializableUnitType<
                SurfaceChargeDensity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
