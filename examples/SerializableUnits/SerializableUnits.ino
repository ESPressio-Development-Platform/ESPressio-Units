#include <Arduino.h>

/*
 * Import one Serializable Unit type only:
 */
#include <ESPressio_Distance_Serializable.hpp>

/*
 * Or import every Serializable Unit type in one batch:
 *
 * #include <ESPressio_SerializableUnits.hpp>
 */

#include <ESPressio_Serializable_JSON.hpp>

using namespace ESPressio;
using namespace ESPressio::Units;

void setup() {
    Serial.begin(115200);

    /*
     * Existing ordinary type remains unchanged and has no Serializable
     * dependency when only ESPressio_Distance.hpp is included.
     */
    Distance<float> ordinary(
        1250.0f,
        Milli
    );

    /*
     * Serializable type is explicitly selected by using the sibling header.
     */
    SerializableDistance<float> serializable(
        1250.0f,
        Milli
    );

    Serializable::JsonArchive archive;

    serializable.Serialize(archive);

    Serial.println(
        archive.ToString().c_str()
    );

    /*
     * Existing values can be promoted on demand.
     */
    auto promoted =
        MakeSerializableUnit(
            ordinary
        );

    (void)promoted;
}

void loop() {
}
