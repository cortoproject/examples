#include "Sub.h"

/* Observer callback function */
CORTO_OBSERVER(onUpdate) {
    /* Convert observable value to string */
    corto_string value = corto_str(observable, 0);

    printf("[sub] %s updated with value %s\n", 
        corto_idof(observable),
        value);

    /* Free resources */
    corto_dealloc(value);
}

int SubMain(int argc, char *argv[]) {

    /* Connect to the corto MQTT broker */
    mqtt_Connector mqttx = mqtt_ConnectorCreateChild(
        root_o,           /* Create connector in root */
        "mqttx",          /* The name of the connector */
        "corto.ws:2000",  /* The address of the MQTT broker */
        root_o);          /* Mount remote objects under root */

    /* Listen for updates in the scope of root */
    corto_observer observer = corto_observerCreate(
        CORTO_ON_UPDATE | CORTO_ON_SCOPE,
        root_o,              
        onUpdate);

    /* Keep application running */
    while (1) {
        corto_sleep(1, 0);
    }

    /* Free resources - though code will never get here */
    corto_delete(observer);
    corto_delete(mqttx);

    return 0;
}
