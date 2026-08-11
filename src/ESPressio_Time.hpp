#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        template <
            typename TValue,
            UnitOrderOfMagnitude TBaseOrderOfMagnitude = Base
        >
        struct Time : public Unit<
            TValue,
            TBaseOrderOfMagnitude,
            UnitContext::Time
        >, public Internal::UnitFactory<
            Time<TValue, TBaseOrderOfMagnitude>,
            TValue,
            UnitContext::Time
        > {
            using Unit<
                TValue,
                TBaseOrderOfMagnitude,
                UnitContext::Time
            >::Unit;
        };

        template <typename TValue> using QuectoSeconds = Time<TValue, Quecto>;
        template <typename TValue> using RontoSeconds = Time<TValue, Ronto>;
        template <typename TValue> using YoctoSeconds = Time<TValue, Yocto>;
        template <typename TValue> using ZeptoSeconds = Time<TValue, Zepto>;
        template <typename TValue> using AttoSeconds = Time<TValue, Atto>;
        template <typename TValue> using FemtoSeconds = Time<TValue, Femto>;
        template <typename TValue> using PicoSeconds = Time<TValue, Pico>;
        template <typename TValue> using NanoSeconds = Time<TValue, Nano>;
        template <typename TValue> using MicroSeconds = Time<TValue, Micro>;
        template <typename TValue> using MilliSeconds = Time<TValue, Milli>;
        template <typename TValue> using CentiSeconds = Time<TValue, Centi>;
        template <typename TValue> using DeciSeconds = Time<TValue, Deci>;
        template <typename TValue> using Seconds = Time<TValue, Base>;
        template <typename TValue> using DecaSeconds = Time<TValue, Deca>;
        template <typename TValue> using HectoSeconds = Time<TValue, Hecto>;
        template <typename TValue> using KiloSeconds = Time<TValue, Kilo>;
        template <typename TValue> using MegaSeconds = Time<TValue, Mega>;
        template <typename TValue> using GigaSeconds = Time<TValue, Giga>;
        template <typename TValue> using TeraSeconds = Time<TValue, Tera>;
        template <typename TValue> using PetaSeconds = Time<TValue, Peta>;
        template <typename TValue> using ExaSeconds = Time<TValue, Exa>;
        template <typename TValue> using ZettaSeconds = Time<TValue, Zetta>;
        template <typename TValue> using YottaSeconds = Time<TValue, Yotta>;
        template <typename TValue> using RonnaSeconds = Time<TValue, Ronna>;
        template <typename TValue> using QuettaSeconds = Time<TValue, Quetta>;

    }

}

using namespace ESPressio::Units;
