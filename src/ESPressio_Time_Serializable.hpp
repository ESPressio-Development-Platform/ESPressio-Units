#pragma once

#include "ESPressio_Time.hpp"
#include "ESPressio_Unit_Serializable.hpp"

namespace ESPressio {

    namespace Units {

        /*
         * Serializable counterpart of Time<TValue, TBaseOrderOfMagnitude>.
         *
         * The template signature intentionally mirrors ESPressio_Time.hpp.
         */
        template<
            typename TValue,
            UnitOrderOfMagnitude TBaseOrderOfMagnitude = Base
        >
        using SerializableTime =
            Internal::SerializableUnitType<
                Time<
                    TValue,
                    TBaseOrderOfMagnitude
                >
            >;

        template<typename TValue> using SerializableQuectoSeconds = SerializableTime<TValue, Quecto>;
        template<typename TValue> using SerializableRontoSeconds = SerializableTime<TValue, Ronto>;
        template<typename TValue> using SerializableYoctoSeconds = SerializableTime<TValue, Yocto>;
        template<typename TValue> using SerializableZeptoSeconds = SerializableTime<TValue, Zepto>;
        template<typename TValue> using SerializableAttoSeconds = SerializableTime<TValue, Atto>;
        template<typename TValue> using SerializableFemtoSeconds = SerializableTime<TValue, Femto>;
        template<typename TValue> using SerializablePicoSeconds = SerializableTime<TValue, Pico>;
        template<typename TValue> using SerializableNanoSeconds = SerializableTime<TValue, Nano>;
        template<typename TValue> using SerializableMicroSeconds = SerializableTime<TValue, Micro>;
        template<typename TValue> using SerializableMilliSeconds = SerializableTime<TValue, Milli>;
        template<typename TValue> using SerializableCentiSeconds = SerializableTime<TValue, Centi>;
        template<typename TValue> using SerializableDeciSeconds = SerializableTime<TValue, Deci>;
        template<typename TValue> using SerializableSeconds = SerializableTime<TValue, Base>;
        template<typename TValue> using SerializableDecaSeconds = SerializableTime<TValue, Deca>;
        template<typename TValue> using SerializableHectoSeconds = SerializableTime<TValue, Hecto>;
        template<typename TValue> using SerializableKiloSeconds = SerializableTime<TValue, Kilo>;
        template<typename TValue> using SerializableMegaSeconds = SerializableTime<TValue, Mega>;
        template<typename TValue> using SerializableGigaSeconds = SerializableTime<TValue, Giga>;
        template<typename TValue> using SerializableTeraSeconds = SerializableTime<TValue, Tera>;
        template<typename TValue> using SerializablePetaSeconds = SerializableTime<TValue, Peta>;
        template<typename TValue> using SerializableExaSeconds = SerializableTime<TValue, Exa>;
        template<typename TValue> using SerializableZettaSeconds = SerializableTime<TValue, Zetta>;
        template<typename TValue> using SerializableYottaSeconds = SerializableTime<TValue, Yotta>;
        template<typename TValue> using SerializableRonnaSeconds = SerializableTime<TValue, Ronna>;
        template<typename TValue> using SerializableQuettaSeconds = SerializableTime<TValue, Quetta>;

    }

}

using namespace ESPressio::Units;
