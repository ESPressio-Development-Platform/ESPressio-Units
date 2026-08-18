#pragma once

#include "ESPressio_ElectromotiveForce.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of ElectromotiveForce<TValue>.
         *
         * Including ESPressio_ElectromotiveForce.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableElectromotiveForce =
            Internal::SerializableUnitType<
                ElectromotiveForce<TValue>
            >;

    }

}

using namespace ESPressio::Units;
