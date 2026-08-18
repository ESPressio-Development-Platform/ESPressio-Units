#pragma once

#include "ESPressio_Radioactivity.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Radioactivity<TValue>.
         *
         * Including ESPressio_Radioactivity.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableRadioactivity =
            Internal::SerializableUnitType<
                Radioactivity<TValue>
            >;

    }

}

using namespace ESPressio::Units;
