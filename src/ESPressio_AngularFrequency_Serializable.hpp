#pragma once

#include "ESPressio_AngularFrequency.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of AngularFrequency<TValue>.
         *
         * Including ESPressio_AngularFrequency.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableAngularFrequency =
            Internal::SerializableUnitType<
                AngularFrequency<TValue>
            >;

    }

}

using namespace ESPressio::Units;
