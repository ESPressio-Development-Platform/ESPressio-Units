#pragma once

#include "ESPressio_AmountOfSubstance.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of AmountOfSubstance<TValue>.
         *
         * Including ESPressio_AmountOfSubstance.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableAmountOfSubstance =
            Internal::SerializableUnitType<
                AmountOfSubstance<TValue>
            >;

    }

}

using namespace ESPressio::Units;
