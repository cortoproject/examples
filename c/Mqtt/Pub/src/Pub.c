#include "Pub.h"

int PubMain(int argc, char *argv[]) {

    /* Connect to the corto MQTT broker */
    mqtt_Connector mqttx = mqtt_ConnectorCreateChild(
        root_o,           /* Create connector in root */
        "mqttx",          /* The name of the connector */
        "corto.ws:2000",  /* The address of the MQTT broker */
        root_o);          /* Mount remote objects under root */

    /* Create an integer object in the root */
    corto_int32 *a = corto_int32CreateChild(root_o, "a", 0);

    /* Update object every second */
    while (1) {
        corto_int32Update(a, *a + 1);
        printf("[pub] updated value of a to %d\n", *a);
        corto_sleep(1, 0);
    }

    /* Free resources - though code will never get here */
    corto_delete(a);
    corto_delete(mqttx);

    return 0;
}
