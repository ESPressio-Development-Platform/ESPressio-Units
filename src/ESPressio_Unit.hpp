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

        /*
            `Unit` pairs a numeric value with its SI order of magnitude.

            Specialised unit types can inherit from this type to retain a
            common value and magnitude representation without introducing
            virtual dispatch or dynamic allocation.
        */
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

            TValue value;
            UnitOrderOfMagnitude orderOfMagnitude;

            static constexpr UnitOrderOfMagnitude baseOrderOfMagnitude =
                TBaseOrderOfMagnitude;
            static constexpr UnitContext context = TContext;

            Unit()
                : value(),
                  orderOfMagnitude(TBaseOrderOfMagnitude) { }

            explicit Unit(
                TValue value,
                UnitOrderOfMagnitude orderOfMagnitude =
                    TBaseOrderOfMagnitude
            ) : value(value), orderOfMagnitude(orderOfMagnitude) { }

            void SetValue(TValue value) {
                this->value = value;
            }

            void SetValue(
                TValue value,
                UnitOrderOfMagnitude orderOfMagnitude
            ) {
                this->value = value;
                this->orderOfMagnitude = orderOfMagnitude;
            }

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

            double ToMagnitude(
                UnitOrderOfMagnitude targetOrderOfMagnitude
            ) const {
                return ToMagnitude<double>(targetOrderOfMagnitude);
            }

            double ToMagnitudeUnchecked(
                UnitOrderOfMagnitude targetOrderOfMagnitude
            ) const {
                return ToMagnitudeUnchecked<double>(
                    targetOrderOfMagnitude
                );
            }

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
