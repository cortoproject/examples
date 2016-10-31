#include "dynamic_bitmask.h"

/* dynamic_bitmask
 *
 * This example shows how to dynamically create a new bitmask type.
 */

int dynamic_bitmaskMain(int argc, char *argv[]) {

    /* Create a new enum */
    corto_bitmask Color = corto_declareChild(root_o, "Color", corto_bitmask_o);
    if (!Color) {
        goto error;
    }

    /* Create constants.
     *
     * Values are automatically assigned, but can be overridden as shown.
     */
    corto_constant *Red = corto_createChild(Color, "Red", corto_constant_o);
    if (!Red) {
        goto error;
    }

    corto_constant *Yellow = corto_createChild(Color, "Yellow", corto_constant_o);
    if (!Yellow) {
        goto error;
    }

    corto_constant *Green = corto_createChild(Color, "Green", corto_constant_o);
    if (!Green) {
        goto error;
    }

    corto_constant *Blue = corto_createChild(Color, "Blue", corto_constant_o);
    if (!Blue) {
        goto error;
    }

    /* Finalize bitmask */
    if (corto_define(Color)) {
        goto error;
    }

    corto_int32 *myColor = corto_createChild(root_o, "myColor", Color);
    if (!myColor) {
        goto error;
    }

    *myColor = *Red | *Blue;
    printf("myColor = %s\n", corto_contentof(NULL, "text/corto", myColor));

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
