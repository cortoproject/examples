
#include <include/dynamic_bitmask.h>

/** dynamic_bitmask
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
    corto_constant 
        *Red = corto_createChild(Color, "Red", corto_constant_o),
        *Yellow = corto_createChild(Color, "Yellow", corto_constant_o),
        *Green = corto_createChild(Color, "Green", corto_constant_o),
        *Blue = corto_createChild(Color, "Blue", corto_constant_o);

    if (!Red || !Yellow || !Green || !Blue) {
        goto error;
    }

    /* Create a constant with a custom value */
    corto_constant 
        *Purple = corto_declareChild(Color, "Purple", corto_constant_o);
        *Purple = *Red | *Blue;
        if (corto_define(Purple)) {
            goto error;
        }

    /* Finalize bitmask */
    if (corto_define(Color)) {
        goto error;
    }

    int32_t myColor = *Yellow | *Blue;
    char *str = corto_ptr_contentof(&myColor, Color, "text/corto");
    corto_info("myColor = '%s'", str);
    corto_dealloc(str);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
