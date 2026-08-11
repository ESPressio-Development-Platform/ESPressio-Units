#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "ESPressio_Units.hpp"

using namespace ESPressio::Units;

namespace {

    struct TestState {
        std::size_t positiveCases = 0;
        std::size_t negativeCases = 0;
        std::size_t failures = 0;

        void Check(
            bool condition,
            const char* typeName,
            const char* caseName,
            bool negative
        ) {
            if (negative) {
                ++negativeCases;
            } else {
                ++positiveCases;
            }

            if (!condition) {
                ++failures;
                std::cerr << typeName << ": " << caseName << " failed\n";
            }
        }
    };

    bool AlmostEqual(
        long double left,
        long double right,
        long double tolerance = 1.0e-12L
    ) {
        const long double scale = std::fmax(
            static_cast<long double>(1),
            std::fmax(std::fabs(left), std::fabs(right))
        );
        return std::fabs(left - right) <= tolerance * scale;
    }

    template <typename TCallback>
    bool ThrowsOverflow(TCallback callback) {
        try {
            callback();
        } catch (const std::overflow_error&) {
            return true;
        } catch (...) {
            return false;
        }
        return false;
    }

    const char* MagnitudeSymbol(UnitOrderOfMagnitude magnitude) {
        switch (magnitude) {
            case Kilo: return "k";
            case Milli: return "m";
            default: return "";
        }
    }

    const char* MagnitudeName(UnitOrderOfMagnitude magnitude) {
        switch (magnitude) {
            case Kilo: return "kilo";
            case Milli: return "milli";
            default: return "";
        }
    }

    template <
        typename TUnit,
        UnitContext TExpectedContext,
        UnitOrderOfMagnitude TExpectedBase
    >
    void RunUnitTypeTests(
        TestState& state,
        const char* typeName,
        const char* expectedSymbol,
        const char* expectedName
    ) {
        static_assert(
            std::is_base_of<
                Unit<double, TExpectedBase, TExpectedContext>,
                TUnit
            >::value,
            "Specialised type must derive from the expected Unit contract"
        );

        state.Check(
            TUnit::context == TExpectedContext,
            typeName,
            "positive/context",
            false
        );
        state.Check(
            TUnit::baseOrderOfMagnitude == TExpectedBase,
            typeName,
            "positive/base magnitude",
            false
        );

        TUnit defaultValue;
        state.Check(
            defaultValue.value == 0.0,
            typeName,
            "positive/default value",
            false
        );
        state.Check(
            defaultValue.orderOfMagnitude == TExpectedBase,
            typeName,
            "positive/default order",
            false
        );

        TUnit canonicalValue(2.0);
        state.Check(
            canonicalValue.value == 2.0,
            typeName,
            "positive/value constructor",
            false
        );
        state.Check(
            canonicalValue.orderOfMagnitude == TExpectedBase,
            typeName,
            "positive/canonical constructor order",
            false
        );

        TUnit explicitMagnitude(3.0, Micro);
        state.Check(
            explicitMagnitude.orderOfMagnitude == Micro,
            typeName,
            "positive/explicit constructor order",
            false
        );

        explicitMagnitude.SetValue(4.0);
        state.Check(
            explicitMagnitude.value == 4.0 &&
                explicitMagnitude.orderOfMagnitude == Micro,
            typeName,
            "positive/value-only setter",
            false
        );

        explicitMagnitude.SetValue(5.0, Mega);
        state.Check(
            explicitMagnitude.value == 5.0 &&
                explicitMagnitude.orderOfMagnitude == Mega,
            typeName,
            "positive/value-and-order setter",
            false
        );

        TUnit baseToDeca(1.0, Base);
        state.Check(
            AlmostEqual(baseToDeca.ToMagnitude(Deca), 0.1L),
            typeName,
            "positive/base-to-deca",
            false
        );

        TUnit petaToFemto(1.0, Peta);
        state.Check(
            AlmostEqual(petaToFemto.ToMagnitude(Femto), 1.0e30L),
            typeName,
            "positive/peta-to-femto",
            false
        );

        state.Check(
            AlmostEqual(
                baseToDeca.template ToMagnitude<float>(Deca),
                0.1L,
                1.0e-6L
            ),
            typeName,
            "positive/float result",
            false
        );

        TUnit roundDown(14.0, Deci);
        state.Check(
            roundDown.template ToMagnitude<int>(Base) == 1,
            typeName,
            "positive/integral round down",
            false
        );

        TUnit roundUp(15.0, Deci);
        state.Check(
            roundUp.template ToMagnitude<int>(Base) == 2,
            typeName,
            "positive/integral round up",
            false
        );

        const std::string expectedSymbolOutput =
            std::string("2 ") + MagnitudeSymbol(TExpectedBase) +
            expectedSymbol;
        state.Check(
            std::string(canonicalValue.AsString().c_str()) ==
                expectedSymbolOutput,
            typeName,
            "positive/symbol string",
            false
        );

        const std::string expectedNameOutput =
            std::string("2 ") + MagnitudeName(TExpectedBase) +
            expectedName;
        state.Check(
            std::string(
                canonicalValue.AsString(UnitRepresentation::Name).c_str()
            ) == expectedNameOutput,
            typeName,
            "positive/name string",
            false
        );

        TUnit positiveFloatOverflow(1.0, Quetta);
        state.Check(
            ThrowsOverflow([&]() {
                positiveFloatOverflow.template ToMagnitude<float>(Quecto);
            }),
            typeName,
            "negative/positive floating overflow",
            true
        );

        TUnit negativeFloatOverflow(-1.0, Quetta);
        state.Check(
            ThrowsOverflow([&]() {
                negativeFloatOverflow.template ToMagnitude<float>(Quecto);
            }),
            typeName,
            "negative/negative floating overflow",
            true
        );

        TUnit positiveSignedOverflow(1.0, Tera);
        state.Check(
            ThrowsOverflow([&]() {
                positiveSignedOverflow.template ToMagnitude<int>(Base);
            }),
            typeName,
            "negative/positive signed overflow",
            true
        );

        TUnit negativeSignedOverflow(-1.0, Tera);
        state.Check(
            ThrowsOverflow([&]() {
                negativeSignedOverflow.template ToMagnitude<int>(Base);
            }),
            typeName,
            "negative/negative signed overflow",
            true
        );

        TUnit positiveUnsignedOverflow(1.0, Tera);
        state.Check(
            ThrowsOverflow([&]() {
                positiveUnsignedOverflow
                    .template ToMagnitude<unsigned int>(Base);
            }),
            typeName,
            "negative/positive unsigned overflow",
            true
        );

        TUnit negativeUnsignedValue(-1.0, Base);
        state.Check(
            ThrowsOverflow([&]() {
                negativeUnsignedValue
                    .template ToMagnitude<unsigned int>(Base);
            }),
            typeName,
            "negative/negative unsigned result",
            true
        );

        TUnit negativeConversion(-2.0, Kilo);
        state.Check(
            AlmostEqual(negativeConversion.ToMagnitude(Base), -2000.0L),
            typeName,
            "negative/negative value conversion",
            true
        );

        TUnit negativeRoundTowardZero(-14.0, Deci);
        state.Check(
            negativeRoundTowardZero.template ToMagnitude<int>(Base) == -1,
            typeName,
            "negative/round below half",
            true
        );

        TUnit negativeHalf(-15.0, Deci);
        state.Check(
            negativeHalf.template ToMagnitude<int>(Base) == -2,
            typeName,
            "negative/round half away from zero",
            true
        );

        TUnit negativeSmall(-4.0, Deci);
        state.Check(
            negativeSmall.template ToMagnitude<int>(Base) == 0,
            typeName,
            "negative/small value rounds to zero",
            true
        );
    }

    void TestMagnitudeRepresentations(TestState& state) {
        struct MagnitudeCase {
            UnitOrderOfMagnitude magnitude;
            const char* symbol;
            const char* name;
        };

        const MagnitudeCase cases[] = {
            {Quecto, "q", "quecto"}, {Ronto, "r", "ronto"},
            {Yocto, "y", "yocto"}, {Zepto, "z", "zepto"},
            {Atto, "a", "atto"}, {Femto, "f", "femto"},
            {Pico, "p", "pico"}, {Nano, "n", "nano"},
            {Micro, "μ", "micro"}, {Milli, "m", "milli"},
            {Centi, "c", "centi"}, {Deci, "d", "deci"},
            {Base, "", ""}, {Deca, "da", "deca"},
            {Hecto, "h", "hecto"}, {Kilo, "k", "kilo"},
            {Mega, "M", "mega"}, {Giga, "G", "giga"},
            {Tera, "T", "tera"}, {Peta, "P", "peta"},
            {Exa, "E", "exa"}, {Zetta, "Z", "zetta"},
            {Yotta, "Y", "yotta"}, {Ronna, "R", "ronna"},
            {Quetta, "Q", "quetta"}
        };

        for (const MagnitudeCase& testCase : cases) {
            state.Check(
                std::string(GetUnitOrderOfMagnitudeSymbol(
                    testCase.magnitude,
                    UnitRepresentation::Symbol
                )) == testCase.symbol,
                "UnitOrderOfMagnitude",
                "positive/symbol mapping",
                false
            );
            state.Check(
                std::string(GetUnitOrderOfMagnitudeSymbol(
                    testCase.magnitude,
                    UnitRepresentation::Name
                )) == testCase.name,
                "UnitOrderOfMagnitude",
                "positive/name mapping",
                false
            );
        }
    }

    void TestFallbackContexts(TestState& state) {
        Unit<int> unknown(7, Kilo);
        state.Check(
            std::string(unknown.AsString().c_str()) == "7",
            "Unit",
            "positive/unknown context string",
            false
        );
        state.Check(
            std::string(GetUnitContextSymbol(
                UnitContext::Other,
                UnitRepresentation::Symbol
            )).empty(),
            "UnitContext",
            "positive/other symbol",
            false
        );
        state.Check(
            std::string(GetUnitContextSymbol(
                UnitContext::Unknown,
                UnitRepresentation::Name
            )) == "unknown",
            "UnitContext",
            "positive/unknown name",
            false
        );
    }

} // namespace

int main() {
    TestState state;

#define ASSERT_TIME_MAGNITUDE(TypeName, Magnitude) \
    static_assert( \
        TypeName<double>::baseOrderOfMagnitude == Magnitude, \
        #TypeName " must use " #Magnitude " as its base magnitude" \
    )

    ASSERT_TIME_MAGNITUDE(QuectoSeconds, Quecto);
    ASSERT_TIME_MAGNITUDE(RontoSeconds, Ronto);
    ASSERT_TIME_MAGNITUDE(YoctoSeconds, Yocto);
    ASSERT_TIME_MAGNITUDE(ZeptoSeconds, Zepto);
    ASSERT_TIME_MAGNITUDE(AttoSeconds, Atto);
    ASSERT_TIME_MAGNITUDE(FemtoSeconds, Femto);
    ASSERT_TIME_MAGNITUDE(PicoSeconds, Pico);
    ASSERT_TIME_MAGNITUDE(NanoSeconds, Nano);
    ASSERT_TIME_MAGNITUDE(MicroSeconds, Micro);
    ASSERT_TIME_MAGNITUDE(MilliSeconds, Milli);
    ASSERT_TIME_MAGNITUDE(CentiSeconds, Centi);
    ASSERT_TIME_MAGNITUDE(DeciSeconds, Deci);
    ASSERT_TIME_MAGNITUDE(Seconds, Base);
    ASSERT_TIME_MAGNITUDE(DecaSeconds, Deca);
    ASSERT_TIME_MAGNITUDE(HectoSeconds, Hecto);
    ASSERT_TIME_MAGNITUDE(KiloSeconds, Kilo);
    ASSERT_TIME_MAGNITUDE(MegaSeconds, Mega);
    ASSERT_TIME_MAGNITUDE(GigaSeconds, Giga);
    ASSERT_TIME_MAGNITUDE(TeraSeconds, Tera);
    ASSERT_TIME_MAGNITUDE(PetaSeconds, Peta);
    ASSERT_TIME_MAGNITUDE(ExaSeconds, Exa);
    ASSERT_TIME_MAGNITUDE(ZettaSeconds, Zetta);
    ASSERT_TIME_MAGNITUDE(YottaSeconds, Yotta);
    ASSERT_TIME_MAGNITUDE(RonnaSeconds, Ronna);
    ASSERT_TIME_MAGNITUDE(QuettaSeconds, Quetta);

#undef ASSERT_TIME_MAGNITUDE

    const Unit<double, Base, UnitContext::StorageCapacity>
        bytesBelowThreshold = StorageCapacity<int>(499)
            .ToNearestWholeMagnitude();
    state.Check(
        bytesBelowThreshold.orderOfMagnitude == Base &&
            AlmostEqual(bytesBelowThreshold.value, 499.0L),
        "StorageCapacity",
        "499 bytes remain bytes",
        false
    );

    const Unit<double, Base, UnitContext::StorageCapacity>
        bytesAtThreshold = StorageCapacity<int>(500)
            .ToNearestWholeMagnitude();
    state.Check(
        bytesAtThreshold.orderOfMagnitude == Kilo &&
            AlmostEqual(bytesAtThreshold.value, 0.5L),
        "StorageCapacity",
        "500 bytes become 0.5 kilobytes",
        false
    );

    const Unit<double, Base, UnitContext::StorageCapacity>
        kilobytesToMegabytes = StorageCapacity<int>(2400, Kilo)
            .ToNearestWholeMagnitude();
    state.Check(
        kilobytesToMegabytes.orderOfMagnitude == Mega &&
            AlmostEqual(kilobytesToMegabytes.value, 2.4L),
        "StorageCapacity",
        "2400 kilobytes become 2.4 megabytes",
        false
    );

    const Unit<double, Base, UnitContext::StorageCapacity>
        negativeThreshold = StorageCapacity<int>(-500)
            .ToNearestWholeMagnitude();
    state.Check(
        negativeThreshold.orderOfMagnitude == Kilo &&
            AlmostEqual(negativeThreshold.value, -0.5L),
        "StorageCapacity",
        "negative values use their absolute size",
        false
    );

    const Unit<double, Base, UnitContext::StorageCapacity>
        zeroMagnitude = StorageCapacity<int>(0, Milli)
            .ToNearestWholeMagnitude();
    state.Check(
        zeroMagnitude.orderOfMagnitude == Milli &&
            AlmostEqual(zeroMagnitude.value, 0.0L),
        "StorageCapacity",
        "zero preserves its existing magnitude",
        false
    );

    const Unit<int, Base, UnitContext::StorageCapacity>
        roundedIntegral = StorageCapacity<int>(500)
            .ToNearestWholeMagnitude<int>();
    state.Check(
        roundedIntegral.orderOfMagnitude == Kilo &&
            roundedIntegral.value == 1,
        "StorageCapacity",
        "integral result follows magnitude rounding policy",
        false
    );

    state.Check(
        StorageCapacity<int>(499).GetNearestWholeMagnitude() == Base &&
            StorageCapacity<int>(500).GetNearestWholeMagnitude() == Kilo,
        "StorageCapacity",
        "nearest magnitude boundary is exposed independently",
        false
    );

    state.Check(
        StorageCapacity<double>(50.0, Deca)
                .GetNearestWholeMagnitude() == Kilo,
        "StorageCapacity",
        "non-engineering input magnitude normalizes to engineering magnitude",
        false
    );

    bool nonFiniteMagnitudeRejected = false;
    try {
        (void) StorageCapacity<double>(
            std::numeric_limits<double>::infinity()
        ).GetNearestWholeMagnitude();
    } catch (const std::domain_error&) {
        nonFiniteMagnitudeRejected = true;
    }
    state.Check(
        nonFiniteMagnitudeRejected,
        "StorageCapacity",
        "non-finite nearest magnitude input is rejected",
        true
    );
    TestMagnitudeRepresentations(state);
    TestFallbackContexts(state);
    RunUnitTypeTests<Dimensionless<double>, UnitContext::Dimensionless, Base>(state, "Dimensionless", "1", "one");
    RunUnitTypeTests<Ratio<double>, UnitContext::Ratio, Base>(state, "Ratio", "1", "ratio");
    RunUnitTypeTests<PlaneAngle<double>, UnitContext::PlaneAngle, Base>(state, "PlaneAngle", "rad", "radian");
    RunUnitTypeTests<SolidAngle<double>, UnitContext::SolidAngle, Base>(state, "SolidAngle", "sr", "steradian");
    RunUnitTypeTests<Time<double>, UnitContext::Time, Base>(state, "Time", "s", "second");
    RunUnitTypeTests<Length<double>, UnitContext::Length, Base>(state, "Length", "m", "metre");
    RunUnitTypeTests<Distance<double>, UnitContext::Distance, Base>(state, "Distance", "m", "metre");
    RunUnitTypeTests<Mass<double>, UnitContext::Mass, Kilo>(state, "Mass", "g", "gram");
    RunUnitTypeTests<ElectricCurrent<double>, UnitContext::ElectricCurrent, Base>(state, "ElectricCurrent", "A", "ampere");
    RunUnitTypeTests<ThermodynamicTemperature<double>, UnitContext::ThermodynamicTemperature, Base>(state, "ThermodynamicTemperature", "K", "kelvin");
    RunUnitTypeTests<AmountOfSubstance<double>, UnitContext::AmountOfSubstance, Base>(state, "AmountOfSubstance", "mol", "mole");
    RunUnitTypeTests<LuminousIntensity<double>, UnitContext::LuminousIntensity, Base>(state, "LuminousIntensity", "cd", "candela");
    RunUnitTypeTests<Area<double>, UnitContext::Area, Base>(state, "Area", "m^2", "square metre");
    RunUnitTypeTests<Volume<double>, UnitContext::Volume, Base>(state, "Volume", "m^3", "cubic metre");
    RunUnitTypeTests<Speed<double>, UnitContext::Speed, Base>(state, "Speed", "m/s", "metre per second");
    RunUnitTypeTests<Velocity<double>, UnitContext::Velocity, Base>(state, "Velocity", "m/s", "metre per second");
    RunUnitTypeTests<Acceleration<double>, UnitContext::Acceleration, Base>(state, "Acceleration", "m/s^2", "metre per second squared");
    RunUnitTypeTests<AngularVelocity<double>, UnitContext::AngularVelocity, Base>(state, "AngularVelocity", "rad/s", "radian per second");
    RunUnitTypeTests<AngularAcceleration<double>, UnitContext::AngularAcceleration, Base>(state, "AngularAcceleration", "rad/s^2", "radian per second squared");
    RunUnitTypeTests<Frequency<double>, UnitContext::Frequency, Base>(state, "Frequency", "Hz", "hertz");
    RunUnitTypeTests<AngularFrequency<double>, UnitContext::AngularFrequency, Base>(state, "AngularFrequency", "rad/s", "radian per second");
    RunUnitTypeTests<Wavenumber<double>, UnitContext::Wavenumber, Base>(state, "Wavenumber", "m^-1", "reciprocal metre");
    RunUnitTypeTests<Force<double>, UnitContext::Force, Base>(state, "Force", "N", "newton");
    RunUnitTypeTests<Weight<double>, UnitContext::Weight, Base>(state, "Weight", "N", "newton");
    RunUnitTypeTests<Pressure<double>, UnitContext::Pressure, Base>(state, "Pressure", "Pa", "pascal");
    RunUnitTypeTests<MechanicalStress<double>, UnitContext::MechanicalStress, Base>(state, "MechanicalStress", "Pa", "pascal");
    RunUnitTypeTests<MomentOfForce<double>, UnitContext::MomentOfForce, Base>(state, "MomentOfForce", "N m", "newton metre");
    RunUnitTypeTests<Torque<double>, UnitContext::Torque, Base>(state, "Torque", "N m", "newton metre");
    RunUnitTypeTests<SurfaceTension<double>, UnitContext::SurfaceTension, Base>(state, "SurfaceTension", "N/m", "newton per metre");
    RunUnitTypeTests<Density<double>, UnitContext::Density, Kilo>(state, "Density", "g/m^3", "gram per cubic metre");
    RunUnitTypeTests<MassDensity<double>, UnitContext::MassDensity, Kilo>(state, "MassDensity", "g/m^3", "gram per cubic metre");
    RunUnitTypeTests<SurfaceDensity<double>, UnitContext::SurfaceDensity, Kilo>(state, "SurfaceDensity", "g/m^2", "gram per square metre");
    RunUnitTypeTests<SpecificVolume<double>, UnitContext::SpecificVolume, Milli>(state, "SpecificVolume", "m^3/g", "cubic metre per gram");
    RunUnitTypeTests<DynamicViscosity<double>, UnitContext::DynamicViscosity, Base>(state, "DynamicViscosity", "Pa s", "pascal second");
    RunUnitTypeTests<KinematicViscosity<double>, UnitContext::KinematicViscosity, Base>(state, "KinematicViscosity", "m^2/s", "square metre per second");
    RunUnitTypeTests<Energy<double>, UnitContext::Energy, Base>(state, "Energy", "J", "joule");
    RunUnitTypeTests<Work<double>, UnitContext::Work, Base>(state, "Work", "J", "joule");
    RunUnitTypeTests<Heat<double>, UnitContext::Heat, Base>(state, "Heat", "J", "joule");
    RunUnitTypeTests<Power<double>, UnitContext::Power, Base>(state, "Power", "W", "watt");
    RunUnitTypeTests<SpecificEnergy<double>, UnitContext::SpecificEnergy, Milli>(state, "SpecificEnergy", "J/g", "joule per gram");
    RunUnitTypeTests<EnergyDensity<double>, UnitContext::EnergyDensity, Base>(state, "EnergyDensity", "J/m^3", "joule per cubic metre");
    RunUnitTypeTests<CelsiusTemperature<double>, UnitContext::CelsiusTemperature, Base>(state, "CelsiusTemperature", "°C", "degree Celsius");
    RunUnitTypeTests<HeatCapacity<double>, UnitContext::HeatCapacity, Base>(state, "HeatCapacity", "J/K", "joule per kelvin");
    RunUnitTypeTests<SpecificHeatCapacity<double>, UnitContext::SpecificHeatCapacity, Milli>(state, "SpecificHeatCapacity", "J/(g K)", "joule per gram kelvin");
    RunUnitTypeTests<Entropy<double>, UnitContext::Entropy, Base>(state, "Entropy", "J/K", "joule per kelvin");
    RunUnitTypeTests<SpecificEntropy<double>, UnitContext::SpecificEntropy, Milli>(state, "SpecificEntropy", "J/(g K)", "joule per gram kelvin");
    RunUnitTypeTests<ThermalConductivity<double>, UnitContext::ThermalConductivity, Base>(state, "ThermalConductivity", "W/(m K)", "watt per metre kelvin");
    RunUnitTypeTests<HeatFluxDensity<double>, UnitContext::HeatFluxDensity, Base>(state, "HeatFluxDensity", "W/m^2", "watt per square metre");
    RunUnitTypeTests<Irradiance<double>, UnitContext::Irradiance, Base>(state, "Irradiance", "W/m^2", "watt per square metre");
    RunUnitTypeTests<ElectricCharge<double>, UnitContext::ElectricCharge, Base>(state, "ElectricCharge", "C", "coulomb");
    RunUnitTypeTests<ElectricPotential<double>, UnitContext::ElectricPotential, Base>(state, "ElectricPotential", "V", "volt");
    RunUnitTypeTests<ElectricPotentialDifference<double>, UnitContext::ElectricPotentialDifference, Base>(state, "ElectricPotentialDifference", "V", "volt");
    RunUnitTypeTests<ElectromotiveForce<double>, UnitContext::ElectromotiveForce, Base>(state, "ElectromotiveForce", "V", "volt");
    RunUnitTypeTests<Capacitance<double>, UnitContext::Capacitance, Base>(state, "Capacitance", "F", "farad");
    RunUnitTypeTests<ElectricResistance<double>, UnitContext::ElectricResistance, Base>(state, "ElectricResistance", "Ω", "ohm");
    RunUnitTypeTests<ElectricConductance<double>, UnitContext::ElectricConductance, Base>(state, "ElectricConductance", "S", "siemens");
    RunUnitTypeTests<CurrentDensity<double>, UnitContext::CurrentDensity, Base>(state, "CurrentDensity", "A/m^2", "ampere per square metre");
    RunUnitTypeTests<ElectricFieldStrength<double>, UnitContext::ElectricFieldStrength, Base>(state, "ElectricFieldStrength", "V/m", "volt per metre");
    RunUnitTypeTests<ElectricChargeDensity<double>, UnitContext::ElectricChargeDensity, Base>(state, "ElectricChargeDensity", "C/m^3", "coulomb per cubic metre");
    RunUnitTypeTests<SurfaceChargeDensity<double>, UnitContext::SurfaceChargeDensity, Base>(state, "SurfaceChargeDensity", "C/m^2", "coulomb per square metre");
    RunUnitTypeTests<ElectricFluxDensity<double>, UnitContext::ElectricFluxDensity, Base>(state, "ElectricFluxDensity", "C/m^2", "coulomb per square metre");
    RunUnitTypeTests<ElectricDisplacement<double>, UnitContext::ElectricDisplacement, Base>(state, "ElectricDisplacement", "C/m^2", "coulomb per square metre");
    RunUnitTypeTests<Permittivity<double>, UnitContext::Permittivity, Base>(state, "Permittivity", "F/m", "farad per metre");
    RunUnitTypeTests<MagneticFieldStrength<double>, UnitContext::MagneticFieldStrength, Base>(state, "MagneticFieldStrength", "A/m", "ampere per metre");
    RunUnitTypeTests<MagneticFlux<double>, UnitContext::MagneticFlux, Base>(state, "MagneticFlux", "Wb", "weber");
    RunUnitTypeTests<MagneticFluxDensity<double>, UnitContext::MagneticFluxDensity, Base>(state, "MagneticFluxDensity", "T", "tesla");
    RunUnitTypeTests<MagnetomotiveForce<double>, UnitContext::MagnetomotiveForce, Base>(state, "MagnetomotiveForce", "A", "ampere");
    RunUnitTypeTests<Inductance<double>, UnitContext::Inductance, Base>(state, "Inductance", "H", "henry");
    RunUnitTypeTests<Permeability<double>, UnitContext::Permeability, Base>(state, "Permeability", "H/m", "henry per metre");
    RunUnitTypeTests<LuminousFlux<double>, UnitContext::LuminousFlux, Base>(state, "LuminousFlux", "lm", "lumen");
    RunUnitTypeTests<Illuminance<double>, UnitContext::Illuminance, Base>(state, "Illuminance", "lx", "lux");
    RunUnitTypeTests<Luminance<double>, UnitContext::Luminance, Base>(state, "Luminance", "cd/m^2", "candela per square metre");
    RunUnitTypeTests<StorageCapacity<double>, UnitContext::StorageCapacity, Base>(state, "StorageCapacity", "B", "byte");
    RunUnitTypeTests<AmountOfSubstanceConcentration<double>, UnitContext::AmountOfSubstanceConcentration, Base>(state, "AmountOfSubstanceConcentration", "mol/m^3", "mole per cubic metre");
    RunUnitTypeTests<MassConcentration<double>, UnitContext::MassConcentration, Kilo>(state, "MassConcentration", "g/m^3", "gram per cubic metre");
    RunUnitTypeTests<MolarEnergy<double>, UnitContext::MolarEnergy, Base>(state, "MolarEnergy", "J/mol", "joule per mole");
    RunUnitTypeTests<MolarEntropy<double>, UnitContext::MolarEntropy, Base>(state, "MolarEntropy", "J/(mol K)", "joule per mole kelvin");
    RunUnitTypeTests<CatalyticActivity<double>, UnitContext::CatalyticActivity, Base>(state, "CatalyticActivity", "kat", "katal");
    RunUnitTypeTests<Radioactivity<double>, UnitContext::Radioactivity, Base>(state, "Radioactivity", "Bq", "becquerel");
    RunUnitTypeTests<AbsorbedDose<double>, UnitContext::AbsorbedDose, Base>(state, "AbsorbedDose", "Gy", "gray");
    RunUnitTypeTests<Kerma<double>, UnitContext::Kerma, Base>(state, "Kerma", "Gy", "gray");
    RunUnitTypeTests<DoseEquivalent<double>, UnitContext::DoseEquivalent, Base>(state, "DoseEquivalent", "Sv", "sievert");
    RunUnitTypeTests<Exposure<double>, UnitContext::Exposure, Milli>(state, "Exposure", "C/g", "coulomb per gram");

    const std::size_t specialisedTypeCount = 83;
    const std::size_t minimumCasesPerPolarity = specialisedTypeCount * 10;
    if (state.positiveCases < minimumCasesPerPolarity ||
        state.negativeCases < minimumCasesPerPolarity) {
        std::cerr << "Required per-type test count was not reached\n";
        return 1;
    }

    std::cout << "Passed " << state.positiveCases
              << " positive and " << state.negativeCases
              << " negative checks across " << specialisedTypeCount
              << " specialised unit types.\n";

    return state.failures == 0 ? 0 : 1;
}
