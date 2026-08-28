#pragma once

#include <Arduino.h>

#include <cmath>
#include <cstddef>
#include <cstdio>
#include <limits>
#include <stdexcept>
#include <type_traits>

#include "ESPressio_UnitEnums.hpp"
#include "ESPressio_UnitConversions.hpp"

namespace ESPressio {

    namespace Units {

        /// <summary>Pairs an arithmetic value with an SI order of magnitude and physical-quantity context.</summary>
        /// <typeparam name="TValue">Non-boolean arithmetic type used to store the unit value.</typeparam>
        /// <typeparam name="TBaseOrderOfMagnitude">Default SI magnitude used when no explicit magnitude is supplied.</typeparam>
        /// <typeparam name="TContext">Physical quantity represented by the unit.</typeparam>
        /// <remarks>Specialized unit types inherit this abstraction to share value, magnitude, formatting, and conversion behavior without virtual dispatch or dynamic allocation.</remarks>
        template <
            typename TValue,
            UnitOrderOfMagnitude TBaseOrderOfMagnitude = Base,
            UnitContext TContext = UnitContext::Unknown
        >
        struct Unit {
            static_assert(
                std::is_arithmetic<TValue>::value &&
                    !std::is_same<
                        typename std::remove_cv<TValue>::type,
                        bool
                    >::value,
                "Unit<TValue, TBaseOrderOfMagnitude, TContext> requires a "
                "non-boolean arithmetic value type"
            );

            /// <summary>Stored numeric value expressed at <c>orderOfMagnitude</c>.</summary>
            TValue value;
            /// <summary>SI order of magnitude associated with the stored value.</summary>
            UnitOrderOfMagnitude orderOfMagnitude;

            /// <summary>Default SI order of magnitude for this unit specialization.</summary>
            static constexpr UnitOrderOfMagnitude baseOrderOfMagnitude =
                TBaseOrderOfMagnitude;
            /// <summary>Physical quantity represented by this unit specialization.</summary>
            static constexpr UnitContext context = TContext;

            /// <summary>Creates a zero-initialized unit at its base order of magnitude.</summary>
            Unit()
                : value(),
                  orderOfMagnitude(TBaseOrderOfMagnitude) { }

            /// <summary>Creates a unit from a value and optional SI order of magnitude.</summary>
            explicit Unit(
                TValue value,
                UnitOrderOfMagnitude orderOfMagnitude =
                    TBaseOrderOfMagnitude
            ) : value(value), orderOfMagnitude(orderOfMagnitude) { }

            /// <summary>Replaces the numeric value while preserving the current order of magnitude.</summary>
            void SetValue(TValue value) {
                this->value = value;
            }

            /// <summary>Replaces both the numeric value and its SI order of magnitude.</summary>
            void SetValue(
                TValue value,
                UnitOrderOfMagnitude orderOfMagnitude
            ) {
                this->value = value;
                this->orderOfMagnitude = orderOfMagnitude;
            }

            /// <summary>Formats the value together with its SI magnitude prefix and unit context.</summary>
            /// <param name="representation">Whether unit metadata is rendered as symbols or full names.</param>
            String AsString(
                UnitRepresentation representation =
                    UnitRepresentation::Symbol
            ) const {
                String result = _valueToString();
                const char* contextRepresentation =
                    GetUnitContextSymbol(TContext, representation);

                if (contextRepresentation[0] == '\0') {
                    return result;
                }

                result += " ";
                result += GetUnitOrderOfMagnitudeSymbol(
                    orderOfMagnitude,
                    representation
                );
                result += contextRepresentation;
                return result;
            }

            /// <summary>Converts this value to another SI order of magnitude as <c>double</c>.</summary>
            /// <remarks>Performs range validation and throws <c>std::overflow_error</c> when the converted value cannot be represented.</remarks>
            double ToMagnitude(
                UnitOrderOfMagnitude targetOrderOfMagnitude
            ) const {
                return ToMagnitude<double>(targetOrderOfMagnitude);
            }

            /// <summary>Converts this value to another SI order of magnitude as <c>double</c> without range validation.</summary>
            double ToMagnitudeUnchecked(
                UnitOrderOfMagnitude targetOrderOfMagnitude
            ) const {
                return ToMagnitudeUnchecked<double>(
                    targetOrderOfMagnitude
                );
            }

            /// <summary>Finds the engineering SI magnitude that gives the nearest practical whole-number representation.</summary>
            /// <returns>The selected engineering order of magnitude.</returns>
            UnitOrderOfMagnitude GetNearestWholeMagnitude() const {
                if (value == static_cast<TValue>(0)) {
                    return orderOfMagnitude;
                }

                static const UnitOrderOfMagnitude engineeringMagnitudes[] = {
                    Quetta,
                    Ronna,
                    Yotta,
                    Zetta,
                    Exa,
                    Peta,
                    Tera,
                    Giga,
                    Mega,
                    Kilo,
                    Base,
                    Milli,
                    Micro,
                    Nano,
                    Pico,
                    Femto,
                    Atto,
                    Zepto,
                    Yocto,
                    Ronto,
                    Quecto
                };

                const long double absoluteValue = std::fabs(
                    static_cast<long double>(value)
                );

                if (!std::isfinite(absoluteValue)) {
                    throw std::domain_error(
                        "A nearest whole magnitude requires a finite value"
                    );
                }

                for (
                    std::size_t index = 0;
                    index < sizeof(engineeringMagnitudes) /
                        sizeof(engineeringMagnitudes[0]);
                    ++index
                ) {
                    const UnitOrderOfMagnitude candidate =
                        engineeringMagnitudes[index];
                    const long double convertedAbsoluteValue =
                        Internal::ConvertMagnitudeValue(
                            absoluteValue,
                            orderOfMagnitude,
                            candidate
                        );

                    if (convertedAbsoluteValue >= 0.5L) {
                        return candidate;
                    }
                }

                return Quecto;
            }

            /// <summary>Returns an equivalent unit expressed at its nearest practical engineering magnitude.</summary>
            /// <typeparam name="TResult">Arithmetic type used to store the converted value.</typeparam>
            template <typename TResult = double>
            Unit<
                TResult,
                TBaseOrderOfMagnitude,
                TContext
            > ToNearestWholeMagnitude() const {
                const UnitOrderOfMagnitude nearestMagnitude =
                    GetNearestWholeMagnitude();

                return Unit<
                    TResult,
                    TBaseOrderOfMagnitude,
                    TContext
                >(
                    ToMagnitude<TResult>(nearestMagnitude),
                    nearestMagnitude
                );
            }

            /// <summary>Converts this value to another SI magnitude using a checked floating-point result type.</summary>
            /// <typeparam name="TResult">Floating-point destination type.</typeparam>
            template <typename TResult>
            typename std::enable_if<
                std::is_floating_point<TResult>::value,
                TResult
            >::type ToMagnitude(
                UnitOrderOfMagnitude targetOrderOfMagnitude
            ) const {
                long double convertedValue = _toMagnitudeAsLongDouble(
                    targetOrderOfMagnitude
                );

                if (!std::isfinite(convertedValue) ||
                    convertedValue <
                        -static_cast<long double>(
                            std::numeric_limits<TResult>::max()
                        ) ||
                    convertedValue >
                        static_cast<long double>(
                            std::numeric_limits<TResult>::max()
                        )) {
                    throw std::overflow_error(
                        "Converted Unit value exceeds the requested "
                        "floating-point result range"
                    );
                }

                return static_cast<TResult>(convertedValue);
            }

            /// <summary>Converts this value to another SI magnitude without checked result-range enforcement.</summary>
            /// <typeparam name="TResult">Non-boolean arithmetic destination type.</typeparam>
            template <typename TResult>
            typename std::enable_if<
                std::is_arithmetic<TResult>::value &&
                    !std::is_same<
                        typename std::remove_cv<TResult>::type,
                        bool
                    >::value,
                TResult
            >::type ToMagnitudeUnchecked(
                UnitOrderOfMagnitude targetOrderOfMagnitude
            ) const {
                return Internal::UncheckedUnitResult<TResult>(
                    _toMagnitudeAsLongDouble(targetOrderOfMagnitude)
                );
            }

            /// <summary>Converts this unit to a directly compatible physical context.</summary>
            /// <typeparam name="TTarget">Target unit template.</typeparam>
            /// <typeparam name="TResult">Arithmetic type used by the target unit.</typeparam>
            template <
                template <typename> class TTarget,
                typename TResult = double
            >
            typename std::enable_if<
                IsDirectUnitContextConversion<
                    TContext,
                    TTarget<TResult>::context
                >::value,
                TTarget<TResult>
            >::type ToContext() const {
                const long double convertedValue =
                    _toMagnitudeAsLongDouble(
                        TTarget<TResult>::baseOrderOfMagnitude
                    );

                return TTarget<TResult>(
                    Internal::CheckedUnitResult<TResult>(convertedValue)
                );
            }

            /// <summary>Converts this value to another SI magnitude using a checked integral result type.</summary>
            /// <typeparam name="TResult">Non-boolean integral destination type.</typeparam>
            /// <remarks>The converted value is rounded before range validation and conversion.</remarks>
            template <typename TResult>
            typename std::enable_if<
                std::is_integral<TResult>::value &&
                    !std::is_same<
                        typename std::remove_cv<TResult>::type,
                        bool
                    >::value,
                TResult
            >::type ToMagnitude(
                UnitOrderOfMagnitude targetOrderOfMagnitude
            ) const {
                long double convertedValue = std::round(
                    _toMagnitudeAsLongDouble(targetOrderOfMagnitude)
                );

                if (!std::isfinite(convertedValue) ||
                    convertedValue <
                        static_cast<long double>(
                            std::numeric_limits<TResult>::lowest()
                        ) ||
                    convertedValue >
                        static_cast<long double>(
                            std::numeric_limits<TResult>::max()
                        )) {
                    throw std::overflow_error(
                        "Converted Unit value exceeds the requested "
                        "integral result range"
                    );
                }

                return static_cast<TResult>(convertedValue);
            }

        private:
            template <typename T = TValue>
            typename std::enable_if<
                std::is_integral<T>::value &&
                    std::is_signed<T>::value,
                String
            >::type _valueToString() const {
                char buffer[32];
                std::snprintf(
                    buffer,
                    sizeof(buffer),
                    "%lld",
                    static_cast<long long>(value)
                );
                return String(buffer);
            }

            template <typename T = TValue>
            typename std::enable_if<
                std::is_integral<T>::value &&
                    std::is_unsigned<T>::value,
                String
            >::type _valueToString() const {
                char buffer[32];
                std::snprintf(
                    buffer,
                    sizeof(buffer),
                    "%llu",
                    static_cast<unsigned long long>(value)
                );
                return String(buffer);
            }

            template <typename T = TValue>
            typename std::enable_if<
                std::is_floating_point<T>::value,
                String
            >::type _valueToString() const {
                char buffer[128];
                std::snprintf(
                    buffer,
                    sizeof(buffer),
                    "%.*Lg",
                    std::numeric_limits<T>::max_digits10,
                    static_cast<long double>(value)
                );
                return String(buffer);
            }

            long double _toMagnitudeAsLongDouble(
                UnitOrderOfMagnitude targetOrderOfMagnitude
            ) const {
                return Internal::ConvertMagnitudeValue(
                    static_cast<long double>(value),
                    orderOfMagnitude,
                    targetOrderOfMagnitude
                );
            }
        };

        template <
            typename TValue,
            UnitOrderOfMagnitude TBaseOrderOfMagnitude,
            UnitContext TContext
        >
        constexpr UnitOrderOfMagnitude Unit<
            TValue,
            TBaseOrderOfMagnitude,
            TContext
        >::baseOrderOfMagnitude;

        template <
            typename TValue,
            UnitOrderOfMagnitude TBaseOrderOfMagnitude,
            UnitContext TContext
        >
        constexpr UnitContext Unit<
            TValue,
            TBaseOrderOfMagnitude,
            TContext
        >::context;

    }

}

using namespace ESPressio::Units;
