/* $CORTO_GENERATED
 *
 * dynamic_enum.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/dynamic_enum.h>

/* $header() */
/* dynamic_enum
 *
 * This example shows how to dynamically create a new enum type.
 */
/* $end */

int dynamic_enumMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a new enum */
    corto_struct Color = corto_declareChild(root_o, "Color", corto_enum_o);
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

    corto_constant *Purple = corto_declareChild(Color, "Purple", corto_constant_o);
    if (!Purple) {
        goto error;
    }
    if (!corto_checkState(Purple, CORTO_DEFINED)) {
        /* Silly example to show how to specify a custom constant value */
        *Purple = 10;
        if (corto_define(Purple)) {
            goto error;
        }
    }

    /* Finalize enumeration */
    if (corto_define(Color)) {
        goto error;
    }

    corto_int32 *myColor = corto_createChild(root_o, "myColor", Color);
    if (!myColor) {
        goto error;
    }

    *myColor = *Purple;
    printf("myColor = %s\n", corto_contentof(NULL, "text/corto", myColor));

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
