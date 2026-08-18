#pragma once

#include "ESPressio_Volume.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Volume<TValue>.
         *
         * Including ESPressio_Volume.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableVolume =
            Internal::SerializableUnitType<
                Volume<TValue>
            >;

    }

}

using namespace ESPressio::Units;
