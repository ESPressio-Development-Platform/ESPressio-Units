#pragma once

#include <cstdint>

namespace ESPressio {

    namespace Units {

        /*
            `UnitOrderOfMagnitude` represents every order of magnitude which
            has an SI prefix.

            Each enumeration value is the corresponding base-10 exponent.
        */
        enum UnitOrderOfMagnitude : int8_t {
            Quecto = -30,
            Ronto = -27,
            Yocto = -24,
            Zepto = -21,
            Atto = -18,
            Femto = -15,
            Pico = -12,
            Nano = -9,
            Micro = -6,
            Milli = -3,
            Centi = -2,
            Deci = -1,
            Base = 0,
            Deca = 1,
            Hecto = 2,
            Kilo = 3,
            Mega = 6,
            Giga = 9,
            Tera = 12,
            Peta = 15,
            Exa = 18,
            Zetta = 21,
            Yotta = 24,
            Ronna = 27,
            Quetta = 30
        };

        /*
            `UnitContext` describes the physical quantity represented by a
            Unit. Contexts remain distinct where quantities share the same SI
            dimensions but have different physical meanings.

            SI derived quantities are unlimited, so `Other` represents valid
            quantity contexts which are not explicitly enumerated here.
        */
        enum class UnitContext : uint8_t {
            Unknown,                        // Unknown or unspecified value
            Other,                          // Specialised derived value

            // Quantities with the unit one
            Dimensionless,                  // One (1)
            Ratio,                          // One (1), ratio, proportion
            PlaneAngle,                     // Radian (rad)
            SolidAngle,                     // Steradian (sr)

            // SI base quantities
            Time,                           // Second (s)
            Length,                         // Metre (m)
            Distance,                       // Metre (m)
            Mass,                           // Gram (g), without magnitude
            ElectricCurrent,                // Ampere (A)
            ThermodynamicTemperature,       // Kelvin (K)
            AmountOfSubstance,              // Mole (mol)
            LuminousIntensity,              // Candela (cd)

            // Spatial and kinematic quantities
            Area,                           // Square metre (m^2)
            Volume,                         // Cubic metre (m^3)
            Speed,                          // Metre per second (m/s)
            Velocity,                       // Metre per second (m/s)
            Acceleration,                   // Metre per second squared (m/s^2)
            AngularVelocity,                // Radian per second (rad/s)
            AngularAcceleration,            // Radian per second squared (rad/s^2)
            Frequency,                      // Hertz (Hz)
            AngularFrequency,               // Radian per second (rad/s)
            Wavenumber,                     // Reciprocal metre (m^-1)

            // Mechanical quantities
            Force,                          // Newton (N)
            Weight,                         // Newton (N)
            Pressure,                       // Pascal (Pa)
            MechanicalStress,               // Pascal (Pa)
            MomentOfForce,                  // Newton metre (N m)
            Torque,                         // Newton metre (N m)
            SurfaceTension,                 // Newton per metre (N/m)
            Density,                        // Gram per cubic metre (g/m^3)
            MassDensity,                    // Gram per cubic metre (g/m^3)
            SurfaceDensity,                 // Gram per square metre (g/m^2)
            SpecificVolume,                 // Cubic metre per gram (m^3/g)
            DynamicViscosity,               // Pascal second (Pa s)
            KinematicViscosity,             // Square metre per second (m^2/s)

            // Energy and thermal quantities
            Energy,                         // Joule (J)
            Work,                           // Joule (J)
            Heat,                           // Joule (J)
            Power,                          // Watt (W)
            SpecificEnergy,                 // Joule per gram (J/g)
            EnergyDensity,                  // Joule per cubic metre (J/m^3)
            CelsiusTemperature,             // Degree Celsius (°C)
            HeatCapacity,                   // Joule per kelvin (J/K)
            SpecificHeatCapacity,           // Joule per gram kelvin (J/(g K))
            Entropy,                        // Joule per kelvin (J/K)
            SpecificEntropy,                // Joule per gram kelvin (J/(g K))
            ThermalConductivity,            // Watt per metre kelvin (W/(m K))
            HeatFluxDensity,                // Watt per square metre (W/m^2)
            Irradiance,                     // Watt per square metre (W/m^2)

            // Electrical quantities
            ElectricCharge,                 // Coulomb (C)
            ElectricPotential,              // Volt (V)
            ElectricPotentialDifference,    // Volt (V), voltage
            ElectromotiveForce,              // Volt (V)
            Capacitance,                     // Farad (F)
            ElectricResistance,              // Ohm (Ω)
            ElectricConductance,             // Siemens (S)
            CurrentDensity,                  // Ampere per square metre (A/m^2)
            ElectricFieldStrength,           // Volt per metre (V/m)
            ElectricChargeDensity,           // Coulomb per cubic metre (C/m^3)
            SurfaceChargeDensity,            // Coulomb per square metre (C/m^2)
            ElectricFluxDensity,             // Coulomb per square metre (C/m^2)
            ElectricDisplacement,            // Coulomb per square metre (C/m^2)
            Permittivity,                    // Farad per metre (F/m)

            // Magnetic quantities
            MagneticFieldStrength,           // Ampere per metre (A/m)
            MagneticFlux,                    // Weber (Wb)
            MagneticFluxDensity,             // Tesla (T)
            MagnetomotiveForce,              // Ampere (A)
            Inductance,                      // Henry (H)
            Permeability,                    // Henry per metre (H/m)

            // Photometric quantities
            LuminousFlux,                    // Lumen (lm)
            Illuminance,                     // Lux (lx)
            Luminance,                       // Candela per square metre (cd/m^2)

            // Digital information quantities
            StorageCapacity,                 // Byte (B)

            // Chemical quantities
            AmountOfSubstanceConcentration,  // Mole per cubic metre (mol/m^3)
            MassConcentration,               // Gram per cubic metre (g/m^3)
            MolarEnergy,                     // Joule per mole (J/mol)
            MolarEntropy,                    // Joule per mole kelvin (J/(mol K))
            CatalyticActivity,               // Katal (kat)

            // Ionizing radiation quantities
            Radioactivity,                   // Becquerel (Bq)
            AbsorbedDose,                    // Gray (Gy)
            Kerma,                           // Gray (Gy)
            DoseEquivalent,                  // Sievert (Sv)
            Exposure                         // Coulomb per gram (C/g)
        };

        enum class UnitRepresentation : uint8_t {
            Symbol, // Abbreviated SI symbol
            Name    // Full name
        };

        /*
            Returns the requested representation of an SI magnitude prefix.

            `Base` returns an empty string because it represents the absence
            of a magnitude prefix.
        */
        inline const char* GetUnitOrderOfMagnitudeSymbol(
            UnitOrderOfMagnitude orderOfMagnitude,
            UnitRepresentation representation
        ) {
            const bool useName =
                representation == UnitRepresentation::Name;

            switch (orderOfMagnitude) {
                case Quecto: return useName ? "quecto" : "q";
                case Ronto: return useName ? "ronto" : "r";
                case Yocto: return useName ? "yocto" : "y";
                case Zepto: return useName ? "zepto" : "z";
                case Atto: return useName ? "atto" : "a";
                case Femto: return useName ? "femto" : "f";
                case Pico: return useName ? "pico" : "p";
                case Nano: return useName ? "nano" : "n";
                case Micro: return useName ? "micro" : "μ";
                case Milli: return useName ? "milli" : "m";
                case Centi: return useName ? "centi" : "c";
                case Deci: return useName ? "deci" : "d";
                case Base: return "";
                case Deca: return useName ? "deca" : "da";
                case Hecto: return useName ? "hecto" : "h";
                case Kilo: return useName ? "kilo" : "k";
                case Mega: return useName ? "mega" : "M";
                case Giga: return useName ? "giga" : "G";
                case Tera: return useName ? "tera" : "T";
                case Peta: return useName ? "peta" : "P";
                case Exa: return useName ? "exa" : "E";
                case Zetta: return useName ? "zetta" : "Z";
                case Yotta: return useName ? "yotta" : "Y";
                case Ronna: return useName ? "ronna" : "R";
                case Quetta: return useName ? "quetta" : "Q";
            }

            return "";
        }

        /*
            Returns the requested magnitude-free representation associated
            with a UnitContext.

            Magnitude prefixes are intentionally excluded so callers can
            format them independently from the physical quantity context.
        */
        inline const char* GetUnitContextSymbol(
            UnitContext context,
            UnitRepresentation representation
        ) {
            const bool useName =
                representation == UnitRepresentation::Name;

            switch (context) {
                case UnitContext::Unknown: return useName ? "unknown" : "";
                case UnitContext::Other: return useName ? "other" : "";
                case UnitContext::Dimensionless: return useName ? "one" : "1";
                case UnitContext::Ratio: return useName ? "ratio" : "1";
                case UnitContext::PlaneAngle: return useName ? "radian" : "rad";
                case UnitContext::SolidAngle: return useName ? "steradian" : "sr";
                case UnitContext::Time: return useName ? "second" : "s";
                case UnitContext::Length: return useName ? "metre" : "m";
                case UnitContext::Distance: return useName ? "metre" : "m";
                case UnitContext::Mass: return useName ? "gram" : "g";
                case UnitContext::ElectricCurrent: return useName ? "ampere" : "A";
                case UnitContext::ThermodynamicTemperature: return useName ? "kelvin" : "K";
                case UnitContext::AmountOfSubstance: return useName ? "mole" : "mol";
                case UnitContext::LuminousIntensity: return useName ? "candela" : "cd";
                case UnitContext::Area: return useName ? "square metre" : "m^2";
                case UnitContext::Volume: return useName ? "cubic metre" : "m^3";
                case UnitContext::Speed: return useName ? "metre per second" : "m/s";
                case UnitContext::Velocity: return useName ? "metre per second" : "m/s";
                case UnitContext::Acceleration: return useName ? "metre per second squared" : "m/s^2";
                case UnitContext::AngularVelocity: return useName ? "radian per second" : "rad/s";
                case UnitContext::AngularAcceleration: return useName ? "radian per second squared" : "rad/s^2";
                case UnitContext::Frequency: return useName ? "hertz" : "Hz";
                case UnitContext::AngularFrequency: return useName ? "radian per second" : "rad/s";
                case UnitContext::Wavenumber: return useName ? "reciprocal metre" : "m^-1";
                case UnitContext::Force: return useName ? "newton" : "N";
                case UnitContext::Weight: return useName ? "newton" : "N";
                case UnitContext::Pressure: return useName ? "pascal" : "Pa";
                case UnitContext::MechanicalStress: return useName ? "pascal" : "Pa";
                case UnitContext::MomentOfForce: return useName ? "newton metre" : "N m";
                case UnitContext::Torque: return useName ? "newton metre" : "N m";
                case UnitContext::SurfaceTension: return useName ? "newton per metre" : "N/m";
                case UnitContext::Density: return useName ? "gram per cubic metre" : "g/m^3";
                case UnitContext::MassDensity: return useName ? "gram per cubic metre" : "g/m^3";
                case UnitContext::SurfaceDensity: return useName ? "gram per square metre" : "g/m^2";
                case UnitContext::SpecificVolume: return useName ? "cubic metre per gram" : "m^3/g";
                case UnitContext::DynamicViscosity: return useName ? "pascal second" : "Pa s";
                case UnitContext::KinematicViscosity: return useName ? "square metre per second" : "m^2/s";
                case UnitContext::Energy: return useName ? "joule" : "J";
                case UnitContext::Work: return useName ? "joule" : "J";
                case UnitContext::Heat: return useName ? "joule" : "J";
                case UnitContext::Power: return useName ? "watt" : "W";
                case UnitContext::SpecificEnergy: return useName ? "joule per gram" : "J/g";
                case UnitContext::EnergyDensity: return useName ? "joule per cubic metre" : "J/m^3";
                case UnitContext::CelsiusTemperature: return useName ? "degree Celsius" : "°C";
                case UnitContext::HeatCapacity: return useName ? "joule per kelvin" : "J/K";
                case UnitContext::SpecificHeatCapacity: return useName ? "joule per gram kelvin" : "J/(g K)";
                case UnitContext::Entropy: return useName ? "joule per kelvin" : "J/K";
                case UnitContext::SpecificEntropy: return useName ? "joule per gram kelvin" : "J/(g K)";
                case UnitContext::ThermalConductivity: return useName ? "watt per metre kelvin" : "W/(m K)";
                case UnitContext::HeatFluxDensity: return useName ? "watt per square metre" : "W/m^2";
                case UnitContext::Irradiance: return useName ? "watt per square metre" : "W/m^2";
                case UnitContext::ElectricCharge: return useName ? "coulomb" : "C";
                case UnitContext::ElectricPotential: return useName ? "volt" : "V";
                case UnitContext::ElectricPotentialDifference: return useName ? "volt" : "V";
                case UnitContext::ElectromotiveForce: return useName ? "volt" : "V";
                case UnitContext::Capacitance: return useName ? "farad" : "F";
                case UnitContext::ElectricResistance: return useName ? "ohm" : "Ω";
                case UnitContext::ElectricConductance: return useName ? "siemens" : "S";
                case UnitContext::CurrentDensity: return useName ? "ampere per square metre" : "A/m^2";
                case UnitContext::ElectricFieldStrength: return useName ? "volt per metre" : "V/m";
                case UnitContext::ElectricChargeDensity: return useName ? "coulomb per cubic metre" : "C/m^3";
                case UnitContext::SurfaceChargeDensity: return useName ? "coulomb per square metre" : "C/m^2";
                case UnitContext::ElectricFluxDensity: return useName ? "coulomb per square metre" : "C/m^2";
                case UnitContext::ElectricDisplacement: return useName ? "coulomb per square metre" : "C/m^2";
                case UnitContext::Permittivity: return useName ? "farad per metre" : "F/m";
                case UnitContext::MagneticFieldStrength: return useName ? "ampere per metre" : "A/m";
                case UnitContext::MagneticFlux: return useName ? "weber" : "Wb";
                case UnitContext::MagneticFluxDensity: return useName ? "tesla" : "T";
                case UnitContext::MagnetomotiveForce: return useName ? "ampere" : "A";
                case UnitContext::Inductance: return useName ? "henry" : "H";
                case UnitContext::Permeability: return useName ? "henry per metre" : "H/m";
                case UnitContext::LuminousFlux: return useName ? "lumen" : "lm";
                case UnitContext::Illuminance: return useName ? "lux" : "lx";
                case UnitContext::Luminance: return useName ? "candela per square metre" : "cd/m^2";
                case UnitContext::StorageCapacity: return useName ? "byte" : "B";
                case UnitContext::AmountOfSubstanceConcentration: return useName ? "mole per cubic metre" : "mol/m^3";
                case UnitContext::MassConcentration: return useName ? "gram per cubic metre" : "g/m^3";
                case UnitContext::MolarEnergy: return useName ? "joule per mole" : "J/mol";
                case UnitContext::MolarEntropy: return useName ? "joule per mole kelvin" : "J/(mol K)";
                case UnitContext::CatalyticActivity: return useName ? "katal" : "kat";
                case UnitContext::Radioactivity: return useName ? "becquerel" : "Bq";
                case UnitContext::AbsorbedDose: return useName ? "gray" : "Gy";
                case UnitContext::Kerma: return useName ? "gray" : "Gy";
                case UnitContext::DoseEquivalent: return useName ? "sievert" : "Sv";
                case UnitContext::Exposure: return useName ? "coulomb per gram" : "C/g";
            }

            return "";
        }

    }

}

using namespace ESPressio::Units;
