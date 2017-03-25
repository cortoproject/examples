/* $CORTO_GENERATED
 *
 * dynamic_primitive.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/dynamic_primitive.h>

/* $header() */
/* dynamic_primitive
 *
 * This example shows how to dynamically create a new primitive type.
 */
/* $end */

int dynamic_primitiveMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a new integer type */
    corto_int _long = corto_declareChild(root_o, "long", corto_int_o);
    if (!_long) {
        goto error;
    }
    if (!corto_checkState(_long, CORTO_DEFINED)) {
        /* Set width member of the baseclass of 'int' (primitive) */
        corto_primitive(_long)->width = CORTO_WIDTH_32;
        if (corto_define(_long)) {
            goto error;
        }
    }

    /* Create a new unsigned integer type */
    corto_int ulong = corto_declareChild(root_o, "ulonglong", corto_uint_o);
    if (!ulong) {
        goto error;
    }
    if (!corto_checkState(ulong, CORTO_DEFINED)) {
        /* Set width member of the baseclass of 'int' (primitive) */
        corto_primitive(ulong)->width = CORTO_WIDTH_64;
        if (corto_define(ulong)) {
            goto error;
        }
    }

    /* Create instance of long */
    int32_t *i = corto_createChild(root_o, "i", _long);
    if (!i) {
        goto error;
    }

    *i = -10;

    printf("i = %s\n", corto_contentof(NULL, "text/corto", i));

    return 0;
error:
    return -1;
/* $end */
}
