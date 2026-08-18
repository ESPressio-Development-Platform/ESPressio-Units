#pragma once

#include "ESPressio_SpecificVolume.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of SpecificVolume<TValue>.
         *
         * Including ESPressio_SpecificVolume.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableSpecificVolume =
            Internal::SerializableUnitType<
                SpecificVolume<TValue>
            >;

    }

}

using namespace ESPressio::Units;
