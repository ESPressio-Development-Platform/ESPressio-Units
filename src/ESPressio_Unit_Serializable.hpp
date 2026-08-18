#pragma once

/*
 * Optional Serializable counterpart infrastructure for ESPressio Units.
 *
 * This header is deliberately separate from ESPressio_Unit.hpp. The normal
 * Unit type does not include, inherit from, or otherwise depend upon
 * ESPressio Serializable.
 */

#if !__has_include(<ESPressio_Serializable.hpp>)
    #error "ESPressio_Unit_Serializable.hpp requires ESPressio-Serializable. Add flowduino/ESPressio-Serializable@^0.9.0 to the consuming project's dependencies."
#endif

#include <tuple>
#include <type_traits>
#include <utility>

#include <ESPressio_Serializable.hpp>

#include "ESPressio_Unit.hpp"

namespace ESPressio {

    namespace Units {

        namespace Internal {

            /*
             * Adds Serializable behaviour to an existing concrete Unit type
             * without modifying that type.
             *
             * No virtual methods are required. ESPressio Serializable uses
             * compile-time CRTP/property traversal, so introducing a vtable
             * into Unit would add overhead without providing a benefit.
             */
            template<typename TUnit>
            struct SerializableUnitType
                : public TUnit,
                  public ::ESPressio::Serializable::Serializable<
                      SerializableUnitType<TUnit>
                  > {

                using UnitType = TUnit;
                using TUnit::TUnit;

                SerializableUnitType() = default;
                SerializableUnitType(
                    const SerializableUnitType&
                ) = default;
                SerializableUnitType(
                    SerializableUnitType&&
                ) = default;

                /*
                 * Allows values returned by existing Unit factories/formulas
                 * to be promoted to the Serializable counterpart only when
                 * serialization is actually required.
                 */
                SerializableUnitType(
                    const TUnit& value
                )
                    : TUnit(value) {
                }

                SerializableUnitType(
                    TUnit&& value
                )
                    : TUnit(std::move(value)) {
                }

                SerializableUnitType& operator=(
                    const TUnit& value
                ) {
                    static_cast<TUnit&>(*this) =
                        value;

                    return *this;
                }

                SerializableUnitType& operator=(
                    TUnit&& value
                ) {
                    static_cast<TUnit&>(*this) =
                        std::move(value);

                    return *this;
                }

                static constexpr uint32_t
                GetSerializableSchemaVersion() {
                    return 1u;
                }

                /*
                 * These are the public per-instance members exposed by Unit.
                 *
                 * baseOrderOfMagnitude and context are compile-time/static
                 * properties of the concrete C++ Unit type and are therefore
                 * not duplicated into serialized instance data.
                 */
                static constexpr auto
                GetSerializableProperties() {
                    return std::make_tuple(
                        ::ESPressio::Serializable::
                            MakeSerializationProperty(
                                "value",
                                &TUnit::value
                            ),

                        ::ESPressio::Serializable::
                            MakeSerializationProperty(
                                "orderOfMagnitude",
                                &TUnit::orderOfMagnitude
                            )
                    );
                }

                TUnit& AsUnit() {
                    return static_cast<TUnit&>(*this);
                }

                const TUnit& AsUnit() const {
                    return static_cast<const TUnit&>(*this);
                }
            };

        } // namespace Internal


        /*
         * Serializable counterpart of the generic Unit type.
         */
        template<
            typename TValue,
            UnitOrderOfMagnitude TBaseOrderOfMagnitude = Base,
            UnitContext TContext = UnitContext::Unknown
        >
        using SerializableUnit =
            Internal::SerializableUnitType<
                Unit<
                    TValue,
                    TBaseOrderOfMagnitude,
                    TContext
                >
            >;


        template<typename TUnit>
        auto MakeSerializableUnit(
            TUnit&& unit
        ) -> Internal::SerializableUnitType<
            typename std::decay<TUnit>::type
        > {
            using UnitType =
                typename std::decay<TUnit>::type;

            return Internal::SerializableUnitType<
                UnitType
            >(
                std::forward<TUnit>(unit)
            );
        }

    }

}

using namespace ESPressio::Units;
