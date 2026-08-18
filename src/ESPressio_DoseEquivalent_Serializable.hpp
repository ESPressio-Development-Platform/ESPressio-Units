#pragma once

#include "ESPressio_DoseEquivalent.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of DoseEquivalent<TValue>.
         *
         * Including ESPressio_DoseEquivalent.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableDoseEquivalent =
            Internal::SerializableUnitType<
                DoseEquivalent<TValue>
            >;

    }

}

using namespace ESPressio::Units;
