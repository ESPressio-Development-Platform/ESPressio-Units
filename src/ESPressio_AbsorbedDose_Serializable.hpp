#pragma once

#include "ESPressio_AbsorbedDose.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of AbsorbedDose<TValue>.
         *
         * Including ESPressio_AbsorbedDose.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableAbsorbedDose =
            Internal::SerializableUnitType<
                AbsorbedDose<TValue>
            >;

    }

}

using namespace ESPressio::Units;
