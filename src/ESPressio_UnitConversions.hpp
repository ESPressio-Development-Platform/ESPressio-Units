#pragma once

#include <cmath>
#include <limits>
#include <stdexcept>
#include <type_traits>

#include "ESPressio_UnitEnums.hpp"

namespace ESPressio {

    namespace Units {

        namespace Internal {

            constexpr long double Pi =
                3.141592653589793238462643383279502884L;

            template <UnitContext TContext>
            struct UnitContextCanonicalMagnitude {
                static constexpr UnitOrderOfMagnitude value = Base;
            };

            template <>
            struct UnitContextCanonicalMagnitude<UnitContext::Mass> {
                static constexpr UnitOrderOfMagnitude value = Kilo;
            };

            template <>
            struct UnitContextCanonicalMagnitude<UnitContext::Density> {
                static constexpr UnitOrderOfMagnitude value = Kilo;
            };

            template <>
            struct UnitContextCanonicalMagnitude<UnitContext::MassDensity> {
                static constexpr UnitOrderOfMagnitude value = Kilo;
            };

            template <>
            struct UnitContextCanonicalMagnitude<UnitContext::SurfaceDensity> {
                static constexpr UnitOrderOfMagnitude value = Kilo;
            };

            template <>
            struct UnitContextCanonicalMagnitude<UnitContext::MassConcentration> {
                static constexpr UnitOrderOfMagnitude value = Kilo;
            };

            template <>
            struct UnitContextCanonicalMagnitude<UnitContext::SpecificVolume> {
                static constexpr UnitOrderOfMagnitude value = Milli;
            };

            template <>
            struct UnitContextCanonicalMagnitude<UnitContext::SpecificEnergy> {
                static constexpr UnitOrderOfMagnitude value = Milli;
            };

            template <>
            struct UnitContextCanonicalMagnitude<
                UnitContext::SpecificHeatCapacity
            > {
                static constexpr UnitOrderOfMagnitude value = Milli;
            };

            template <>
            struct UnitContextCanonicalMagnitude<UnitContext::SpecificEntropy> {
                static constexpr UnitOrderOfMagnitude value = Milli;
            };

            template <>
            struct UnitContextCanonicalMagnitude<UnitContext::Exposure> {
                static constexpr UnitOrderOfMagnitude value = Milli;
            };

            inline long double PowerOfTen(unsigned exponent) {
                long double result = 1.0L;
                long double factor = 10.0L;

                while (exponent != 0U) {
                    if ((exponent & 1U) != 0U) {
                        result *= factor;
                    }
                    factor *= factor;
                    exponent >>= 1U;
                }

                return result;
            }

            constexpr long double CompileTimePowerOfTen(
                unsigned exponent
            ) {
                return exponent == 0U
                    ? 1.0L
                    : 10.0L * CompileTimePowerOfTen(exponent - 1U);
            }

            inline long double ConvertMagnitudeValue(
                long double value,
                UnitOrderOfMagnitude source,
                UnitOrderOfMagnitude target
            ) {
                const int exponentDifference =
                    static_cast<int>(source) - static_cast<int>(target);

                if (exponentDifference == 0) {
                    return value;
                }

                const unsigned absoluteExponent = static_cast<unsigned>(
                    exponentDifference < 0
                        ? -exponentDifference
                        : exponentDifference
                );
                const long double scale = PowerOfTen(absoluteExponent);

                return exponentDifference < 0
                    ? value / scale
                    : value * scale;
            }

            template <
                UnitOrderOfMagnitude TSource,
                UnitOrderOfMagnitude TTarget
            >
            struct CompileTimeMagnitudeConverter {
                static long double Convert(long double value) {
                    return static_cast<int>(TSource) <
                            static_cast<int>(TTarget)
                        ? value / CompileTimePowerOfTen(
                            static_cast<unsigned>(
                                static_cast<int>(TTarget) -
                                static_cast<int>(TSource)
                            )
                        )
                        : value * CompileTimePowerOfTen(
                            static_cast<unsigned>(
                                static_cast<int>(TSource) -
                                static_cast<int>(TTarget)
                            )
                        );
                }
            };

            template <UnitOrderOfMagnitude TMagnitude>
            struct CompileTimeMagnitudeConverter<TMagnitude, TMagnitude> {
                static long double Convert(long double value) {
                    return value;
                }
            };

            inline long double SafeDivide(
                long double numerator,
                long double denominator
            ) {
                if (denominator == 0.0L) {
                    throw std::domain_error(
                        "A Unit conversion formula cannot divide by zero"
                    );
                }
                return numerator / denominator;
            }

            template <typename TUnit>
            long double CanonicalValue(const TUnit& unit) {
                const UnitOrderOfMagnitude canonicalMagnitude =
                    UnitContextCanonicalMagnitude<TUnit::context>::value;

                if (unit.orderOfMagnitude == canonicalMagnitude) {
                    return static_cast<long double>(unit.value);
                }

                return unit.template ToMagnitude<long double>(
                    canonicalMagnitude
                );
            }

            template <typename TResult>
            typename std::enable_if<
                std::is_floating_point<TResult>::value,
                TResult
            >::type CheckedUnitResult(long double value) {
                if (!std::isfinite(value) ||
                    value < -static_cast<long double>(
                        std::numeric_limits<TResult>::max()
                    ) ||
                    value > static_cast<long double>(
                        std::numeric_limits<TResult>::max()
                    )) {
                    throw std::overflow_error(
                        "Calculated Unit value exceeds the requested "
                        "floating-point result range"
                    );
                }
                return static_cast<TResult>(value);
            }

            template <typename TResult>
            typename std::enable_if<
                std::is_integral<TResult>::value &&
                    !std::is_same<
                        typename std::remove_cv<TResult>::type,
                        bool
                    >::value,
                TResult
            >::type CheckedUnitResult(long double value) {
                const long double roundedValue = std::round(value);
                if (!std::isfinite(roundedValue) ||
                    roundedValue < static_cast<long double>(
                        std::numeric_limits<TResult>::lowest()
                    ) ||
                    roundedValue > static_cast<long double>(
                        std::numeric_limits<TResult>::max()
                    )) {
                    throw std::overflow_error(
                        "Calculated Unit value exceeds the requested "
                        "integral result range"
                    );
                }
                return static_cast<TResult>(roundedValue);
            }

            template <typename TResult>
            typename std::enable_if<
                std::is_floating_point<TResult>::value,
                TResult
            >::type UncheckedUnitResult(long double value) {
                return static_cast<TResult>(value);
            }

            template <typename TResult>
            typename std::enable_if<
                std::is_integral<TResult>::value &&
                    !std::is_same<
                        typename std::remove_cv<TResult>::type,
                        bool
                    >::value,
                TResult
            >::type UncheckedUnitResult(long double value) {
                return static_cast<TResult>(std::round(value));
            }

            template <typename T, typename = void>
            struct HasUnitMetadata : std::false_type { };

            template <typename T>
            struct HasUnitMetadata<
                T,
                decltype(
                    static_cast<void>(T::context),
                    static_cast<void>(T::baseOrderOfMagnitude),
                    void()
                )
            > : std::true_type { };

            template <typename... TInputs>
            struct AllUnitInputs;

            template <>
            struct AllUnitInputs<> : std::true_type { };

            template <typename TFirst, typename... TRest>
            struct AllUnitInputs<TFirst, TRest...> :
                std::integral_constant<
                    bool,
                    HasUnitMetadata<
                        typename std::decay<TFirst>::type
                    >::value &&
                    AllUnitInputs<TRest...>::value
                > { };

            template <
                UnitContext TTargetContext,
                UnitContext... TSourceContexts
            >
            struct UnitFormula;

            template <
                typename TDerived,
                typename TValue,
                UnitContext TTargetContext
            >
            struct UnitFactory {
                template <typename... TInputs>
                static typename std::enable_if<
                    std::is_convertible<
                        decltype(UnitFormula<
                            TTargetContext,
                            std::decay<TInputs>::type::context...
                        >::Calculate(
                            std::declval<const TInputs&>()...
                        )),
                        long double
                    >::value,
                    TDerived
                >::type From(const TInputs&... inputs) {
                    const long double calculatedValue = UnitFormula<
                        TTargetContext,
                        std::decay<TInputs>::type::context...
                    >::Calculate(inputs...);

                    const long double storedValue =
                        CompileTimeMagnitudeConverter<
                            UnitContextCanonicalMagnitude<
                                TTargetContext
                            >::value,
                            TDerived::baseOrderOfMagnitude
                        >::Convert(calculatedValue);

                    return TDerived(
                        CheckedUnitResult<TValue>(storedValue)
                    );
                }

                template <typename... TInputs>
                static typename std::enable_if<
                    std::is_convertible<
                        decltype(UnitFormula<
                            TTargetContext,
                            std::decay<TInputs>::type::context...
                        >::Calculate(
                            std::declval<const TInputs&>()...
                        )),
                        long double
                    >::value,
                    TDerived
                >::type FromUnchecked(const TInputs&... inputs) {
                    const long double calculatedValue = UnitFormula<
                        TTargetContext,
                        std::decay<TInputs>::type::context...
                    >::Calculate(inputs...);
                    const long double storedValue =
                        CompileTimeMagnitudeConverter<
                            UnitContextCanonicalMagnitude<
                                TTargetContext
                            >::value,
                            TDerived::baseOrderOfMagnitude
                        >::Convert(calculatedValue);

                    return TDerived(
                        UncheckedUnitResult<TValue>(storedValue)
                    );
                }
            };

        } // namespace Internal

        template <UnitContext TSource, UnitContext TTarget>
        struct IsDirectUnitContextConversion : std::false_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Length,
            UnitContext::Distance
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Distance,
            UnitContext::Length
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Speed,
            UnitContext::Velocity
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Velocity,
            UnitContext::Speed
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Force,
            UnitContext::Weight
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Weight,
            UnitContext::Force
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Pressure,
            UnitContext::MechanicalStress
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::MechanicalStress,
            UnitContext::Pressure
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::MomentOfForce,
            UnitContext::Torque
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Torque,
            UnitContext::MomentOfForce
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Density,
            UnitContext::MassDensity
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::MassDensity,
            UnitContext::Density
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Energy,
            UnitContext::Work
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Energy,
            UnitContext::Heat
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Work,
            UnitContext::Energy
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Work,
            UnitContext::Heat
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Heat,
            UnitContext::Energy
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::Heat,
            UnitContext::Work
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::ElectricPotential,
            UnitContext::ElectricPotentialDifference
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::ElectricPotential,
            UnitContext::ElectromotiveForce
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::ElectricPotentialDifference,
            UnitContext::ElectricPotential
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::ElectricPotentialDifference,
            UnitContext::ElectromotiveForce
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::ElectromotiveForce,
            UnitContext::ElectricPotential
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::ElectromotiveForce,
            UnitContext::ElectricPotentialDifference
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::ElectricFluxDensity,
            UnitContext::ElectricDisplacement
        > : std::true_type { };

        template <>
        struct IsDirectUnitContextConversion<
            UnitContext::ElectricDisplacement,
            UnitContext::ElectricFluxDensity
        > : std::true_type { };

        namespace Internal {

            template <>
            struct UnitFormula<
                UnitContext::Length,
                UnitContext::Distance
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Distance,
                UnitContext::Length
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Speed,
                UnitContext::Velocity
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Velocity,
                UnitContext::Speed
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Force,
                UnitContext::Weight
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Weight,
                UnitContext::Force
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Pressure,
                UnitContext::MechanicalStress
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MechanicalStress,
                UnitContext::Pressure
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MomentOfForce,
                UnitContext::Torque
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Torque,
                UnitContext::MomentOfForce
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Density,
                UnitContext::MassDensity
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MassDensity,
                UnitContext::Density
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Energy,
                UnitContext::Work
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Energy,
                UnitContext::Heat
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Work,
                UnitContext::Energy
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Work,
                UnitContext::Heat
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Heat,
                UnitContext::Energy
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Heat,
                UnitContext::Work
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricPotential,
                UnitContext::ElectricPotentialDifference
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricPotential,
                UnitContext::ElectromotiveForce
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricPotentialDifference,
                UnitContext::ElectricPotential
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricPotentialDifference,
                UnitContext::ElectromotiveForce
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectromotiveForce,
                UnitContext::ElectricPotential
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectromotiveForce,
                UnitContext::ElectricPotentialDifference
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricFluxDensity,
                UnitContext::ElectricDisplacement
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricDisplacement,
                UnitContext::ElectricFluxDensity
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Frequency,
                UnitContext::Time
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return SafeDivide(1.0L, CanonicalValue(source));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Time,
                UnitContext::Frequency
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return SafeDivide(1.0L, CanonicalValue(source));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::AngularFrequency,
                UnitContext::Frequency
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return 2.0L * Pi * CanonicalValue(source);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Frequency,
                UnitContext::AngularFrequency
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return SafeDivide(CanonicalValue(source), 2.0L * Pi);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ThermodynamicTemperature,
                UnitContext::CelsiusTemperature
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source) + 273.15L;
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::CelsiusTemperature,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return CanonicalValue(source) - 273.15L;
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricConductance,
                UnitContext::ElectricResistance
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return SafeDivide(1.0L, CanonicalValue(source));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricResistance,
                UnitContext::ElectricConductance
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return SafeDivide(1.0L, CanonicalValue(source));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Wavenumber,
                UnitContext::Length
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return SafeDivide(1.0L, CanonicalValue(source));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Wavenumber,
                UnitContext::Distance
            > {
                template <typename TSource>
                static long double Calculate(const TSource& source) {
                    return SafeDivide(1.0L, CanonicalValue(source));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Area,
                UnitContext::Length,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Area,
                UnitContext::Length,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Area,
                UnitContext::Distance,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Area,
                UnitContext::Distance,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Volume,
                UnitContext::Area,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Volume,
                UnitContext::Area,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Speed,
                UnitContext::Length,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Speed,
                UnitContext::Distance,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Velocity,
                UnitContext::Length,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Velocity,
                UnitContext::Distance,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Acceleration,
                UnitContext::Speed,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Acceleration,
                UnitContext::Velocity,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::AngularVelocity,
                UnitContext::PlaneAngle,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::AngularAcceleration,
                UnitContext::AngularVelocity,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Force,
                UnitContext::Mass,
                UnitContext::Acceleration
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Weight,
                UnitContext::Mass,
                UnitContext::Acceleration
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Pressure,
                UnitContext::Force,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Pressure,
                UnitContext::Weight,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MechanicalStress,
                UnitContext::Force,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MechanicalStress,
                UnitContext::Weight,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MomentOfForce,
                UnitContext::Force,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MomentOfForce,
                UnitContext::Force,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MomentOfForce,
                UnitContext::Weight,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MomentOfForce,
                UnitContext::Weight,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Torque,
                UnitContext::Force,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Torque,
                UnitContext::Force,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Torque,
                UnitContext::Weight,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Torque,
                UnitContext::Weight,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SurfaceTension,
                UnitContext::Force,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SurfaceTension,
                UnitContext::Force,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SurfaceTension,
                UnitContext::Weight,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SurfaceTension,
                UnitContext::Weight,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Density,
                UnitContext::Mass,
                UnitContext::Volume
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MassDensity,
                UnitContext::Mass,
                UnitContext::Volume
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SurfaceDensity,
                UnitContext::Mass,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SpecificVolume,
                UnitContext::Volume,
                UnitContext::Mass
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::DynamicViscosity,
                UnitContext::Pressure,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::DynamicViscosity,
                UnitContext::MechanicalStress,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::KinematicViscosity,
                UnitContext::DynamicViscosity,
                UnitContext::Density
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::KinematicViscosity,
                UnitContext::DynamicViscosity,
                UnitContext::MassDensity
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Energy,
                UnitContext::Force,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Energy,
                UnitContext::Force,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Energy,
                UnitContext::Weight,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Energy,
                UnitContext::Weight,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Work,
                UnitContext::Force,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Work,
                UnitContext::Force,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Work,
                UnitContext::Weight,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Work,
                UnitContext::Weight,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Heat,
                UnitContext::Force,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Heat,
                UnitContext::Force,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Heat,
                UnitContext::Weight,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Heat,
                UnitContext::Weight,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Energy,
                UnitContext::Power,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Work,
                UnitContext::Power,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Heat,
                UnitContext::Power,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Power,
                UnitContext::Energy,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Power,
                UnitContext::Work,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Power,
                UnitContext::Heat,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Power,
                UnitContext::Force,
                UnitContext::Speed
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Power,
                UnitContext::Force,
                UnitContext::Velocity
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Power,
                UnitContext::Weight,
                UnitContext::Speed
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Power,
                UnitContext::Weight,
                UnitContext::Velocity
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SpecificEnergy,
                UnitContext::Energy,
                UnitContext::Mass
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SpecificEnergy,
                UnitContext::Work,
                UnitContext::Mass
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SpecificEnergy,
                UnitContext::Heat,
                UnitContext::Mass
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::EnergyDensity,
                UnitContext::Energy,
                UnitContext::Volume
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::EnergyDensity,
                UnitContext::Work,
                UnitContext::Volume
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::EnergyDensity,
                UnitContext::Heat,
                UnitContext::Volume
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::HeatCapacity,
                UnitContext::Energy,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::HeatCapacity,
                UnitContext::Heat,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Entropy,
                UnitContext::Energy,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Entropy,
                UnitContext::Heat,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::HeatFluxDensity,
                UnitContext::Power,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Irradiance,
                UnitContext::Power,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricCharge,
                UnitContext::ElectricCurrent,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricPotential,
                UnitContext::Energy,
                UnitContext::ElectricCharge
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricPotential,
                UnitContext::Work,
                UnitContext::ElectricCharge
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricPotentialDifference,
                UnitContext::Energy,
                UnitContext::ElectricCharge
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricPotentialDifference,
                UnitContext::Work,
                UnitContext::ElectricCharge
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectromotiveForce,
                UnitContext::Energy,
                UnitContext::ElectricCharge
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectromotiveForce,
                UnitContext::Work,
                UnitContext::ElectricCharge
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricPotential,
                UnitContext::Power,
                UnitContext::ElectricCurrent
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricPotentialDifference,
                UnitContext::Power,
                UnitContext::ElectricCurrent
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectromotiveForce,
                UnitContext::Power,
                UnitContext::ElectricCurrent
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Capacitance,
                UnitContext::ElectricCharge,
                UnitContext::ElectricPotential
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Capacitance,
                UnitContext::ElectricCharge,
                UnitContext::ElectricPotentialDifference
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Capacitance,
                UnitContext::ElectricCharge,
                UnitContext::ElectromotiveForce
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricResistance,
                UnitContext::ElectricPotential,
                UnitContext::ElectricCurrent
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricResistance,
                UnitContext::ElectricPotentialDifference,
                UnitContext::ElectricCurrent
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricResistance,
                UnitContext::ElectromotiveForce,
                UnitContext::ElectricCurrent
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricConductance,
                UnitContext::ElectricCurrent,
                UnitContext::ElectricPotential
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricConductance,
                UnitContext::ElectricCurrent,
                UnitContext::ElectricPotentialDifference
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricConductance,
                UnitContext::ElectricCurrent,
                UnitContext::ElectromotiveForce
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::CurrentDensity,
                UnitContext::ElectricCurrent,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricFieldStrength,
                UnitContext::ElectricPotential,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricFieldStrength,
                UnitContext::ElectricPotential,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricFieldStrength,
                UnitContext::ElectricPotentialDifference,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricFieldStrength,
                UnitContext::ElectricPotentialDifference,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricFieldStrength,
                UnitContext::ElectromotiveForce,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricFieldStrength,
                UnitContext::ElectromotiveForce,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricChargeDensity,
                UnitContext::ElectricCharge,
                UnitContext::Volume
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SurfaceChargeDensity,
                UnitContext::ElectricCharge,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricFluxDensity,
                UnitContext::ElectricCharge,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ElectricDisplacement,
                UnitContext::ElectricCharge,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Permittivity,
                UnitContext::Capacitance,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Permittivity,
                UnitContext::Capacitance,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MagneticFieldStrength,
                UnitContext::ElectricCurrent,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MagneticFieldStrength,
                UnitContext::ElectricCurrent,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MagneticFlux,
                UnitContext::ElectricPotential,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MagneticFlux,
                UnitContext::ElectricPotentialDifference,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MagneticFlux,
                UnitContext::ElectromotiveForce,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MagneticFluxDensity,
                UnitContext::MagneticFlux,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MagnetomotiveForce,
                UnitContext::ElectricCurrent,
                UnitContext::Ratio
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MagnetomotiveForce,
                UnitContext::ElectricCurrent,
                UnitContext::Dimensionless
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Inductance,
                UnitContext::MagneticFlux,
                UnitContext::ElectricCurrent
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Permeability,
                UnitContext::Inductance,
                UnitContext::Length
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Permeability,
                UnitContext::Inductance,
                UnitContext::Distance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::LuminousFlux,
                UnitContext::LuminousIntensity,
                UnitContext::SolidAngle
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Illuminance,
                UnitContext::LuminousFlux,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Luminance,
                UnitContext::LuminousIntensity,
                UnitContext::Area
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::AmountOfSubstanceConcentration,
                UnitContext::AmountOfSubstance,
                UnitContext::Volume
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MassConcentration,
                UnitContext::Mass,
                UnitContext::Volume
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MolarEnergy,
                UnitContext::Energy,
                UnitContext::AmountOfSubstance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MolarEnergy,
                UnitContext::Work,
                UnitContext::AmountOfSubstance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MolarEnergy,
                UnitContext::Heat,
                UnitContext::AmountOfSubstance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::MolarEntropy,
                UnitContext::Entropy,
                UnitContext::AmountOfSubstance
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::CatalyticActivity,
                UnitContext::AmountOfSubstance,
                UnitContext::Time
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::AbsorbedDose,
                UnitContext::Energy,
                UnitContext::Mass
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Kerma,
                UnitContext::Energy,
                UnitContext::Mass
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::DoseEquivalent,
                UnitContext::AbsorbedDose,
                UnitContext::Ratio
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::DoseEquivalent,
                UnitContext::AbsorbedDose,
                UnitContext::Dimensionless
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::DoseEquivalent,
                UnitContext::Kerma,
                UnitContext::Ratio
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::DoseEquivalent,
                UnitContext::Kerma,
                UnitContext::Dimensionless
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return CanonicalValue(left) * CanonicalValue(right);
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::Exposure,
                UnitContext::ElectricCharge,
                UnitContext::Mass
            > {
                template <typename TLeft, typename TRight>
                static long double Calculate(
                    const TLeft& left,
                    const TRight& right
                ) {
                    return SafeDivide(CanonicalValue(left), CanonicalValue(right));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SpecificHeatCapacity,
                UnitContext::Energy,
                UnitContext::Mass,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TFirst, typename TSecond, typename TThird>
                static long double Calculate(
                    const TFirst& first,
                    const TSecond& second,
                    const TThird& third
                ) {
                    return SafeDivide(CanonicalValue(first), CanonicalValue(second) * CanonicalValue(third));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SpecificHeatCapacity,
                UnitContext::Heat,
                UnitContext::Mass,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TFirst, typename TSecond, typename TThird>
                static long double Calculate(
                    const TFirst& first,
                    const TSecond& second,
                    const TThird& third
                ) {
                    return SafeDivide(CanonicalValue(first), CanonicalValue(second) * CanonicalValue(third));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SpecificEntropy,
                UnitContext::Energy,
                UnitContext::Mass,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TFirst, typename TSecond, typename TThird>
                static long double Calculate(
                    const TFirst& first,
                    const TSecond& second,
                    const TThird& third
                ) {
                    return SafeDivide(CanonicalValue(first), CanonicalValue(second) * CanonicalValue(third));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::SpecificEntropy,
                UnitContext::Heat,
                UnitContext::Mass,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TFirst, typename TSecond, typename TThird>
                static long double Calculate(
                    const TFirst& first,
                    const TSecond& second,
                    const TThird& third
                ) {
                    return SafeDivide(CanonicalValue(first), CanonicalValue(second) * CanonicalValue(third));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ThermalConductivity,
                UnitContext::Power,
                UnitContext::Length,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TFirst, typename TSecond, typename TThird>
                static long double Calculate(
                    const TFirst& first,
                    const TSecond& second,
                    const TThird& third
                ) {
                    return SafeDivide(CanonicalValue(first), CanonicalValue(second) * CanonicalValue(third));
                }
            };

            template <>
            struct UnitFormula<
                UnitContext::ThermalConductivity,
                UnitContext::Power,
                UnitContext::Distance,
                UnitContext::ThermodynamicTemperature
            > {
                template <typename TFirst, typename TSecond, typename TThird>
                static long double Calculate(
                    const TFirst& first,
                    const TSecond& second,
                    const TThird& third
                ) {
                    return SafeDivide(CanonicalValue(first), CanonicalValue(second) * CanonicalValue(third));
                }
            };

        } // namespace Internal

    } // namespace Units

} // namespace ESPressio
