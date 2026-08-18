#pragma once

#include "ESPressio_Work.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of Work<TValue>.
         *
         * Including ESPressio_Work.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableWork =
            Internal::SerializableUnitType<
                Work<TValue>
            >;

    }

}

using namespace ESPressio::Units;
