#pragma once

#include "ESPressio_MagnetomotiveForce.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Optional Serializable counterpart of MagnetomotiveForce<TValue>.
         *
         * Including ESPressio_MagnetomotiveForce.hpp alone does not require
         * ESPressio Serializable.
         */
        template<typename TValue>
        using SerializableMagnetomotiveForce =
            Internal::SerializableUnitType<
                MagnetomotiveForce<TValue>
            >;

    }

}

using namespace ESPressio::Units;
