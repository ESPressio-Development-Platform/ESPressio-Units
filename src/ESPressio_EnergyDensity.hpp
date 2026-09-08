#pragma once

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

                /**
         * ESPressio Memory Audit
         * Inherited Memory Total: 1 bytes known/aligned storage + sizeof(TValue) [0 bytes dynamic allocation]
         * Members: none (standalone empty object occupies 1 byte; an eligible empty base may be optimized to 0 bytes).
         * Total Memory: 1 bytes known/aligned storage + sizeof(TValue) [0 bytes dynamic allocation]
         * Basis: ESP32/Xtensa ILP32 reference ABI (4-byte pointers/size_t); ESPressio stateful allocators/deleters included; ABI-sensitive STL/platform internals are identified explicitly.
         * Confidence: low; compile-time sizeof on the concrete target remains authoritative for ABI-sensitive/opaque members.
         * End ESPressio Memory Audit
         */
template <typename TValue>
        struct EnergyDensity : public Unit<
            TValue,
            Base,
            UnitContext::EnergyDensity
        >, public Internal::UnitFactory<
            EnergyDensity<TValue>,
            TValue,
            UnitContext::EnergyDensity
        > {
            using Unit<
                TValue,
                Base,
                UnitContext::EnergyDensity
            >::Unit;
        };

    }

}

using namespace ESPressio::Units;
