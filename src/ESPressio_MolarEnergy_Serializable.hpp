#pragma once

#include "ESPressio_MolarEnergy.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of MolarEnergy<TValue>.
         *
         * Including ESPressio_MolarEnergy.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableMolarEnergy =
            Internal::SerializableUnitType<
                MolarEnergy<TValue>
            >;

    }

}

using namespace ESPressio::Units;
