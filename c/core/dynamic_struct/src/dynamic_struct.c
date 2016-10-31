#include "dynamic_struct.h"

/* dynamic_struct
 *
 * This example shows how to dynamically create a new struct type.
 */

int dynamic_structMain(int argc, char *argv[]) {

    /* Create a new struct */
    corto_struct Point = corto_declareChild(root_o, "Point", corto_struct_o);
    if (!Point) {
        goto error;
    }

    /* Create x member */
    corto_member x = corto_declareChild(Point, "x", corto_member_o);
    if (!x) {
        goto error;
    }
    if (!corto_checkState(x, CORTO_DEFINED)) {
        corto_setref(&x->type, corto_int32_o);
        if (corto_define(x)) {
            goto error;
        }
    }

    /* Create y member */
    corto_member y = corto_declareChild(Point, "y", corto_member_o);
    if (!y) {
        goto error;
    }
    if (!corto_checkState(y, CORTO_DEFINED)) {
        corto_setref(&y->type, corto_int32_o);
        if (corto_define(y)) {
            goto error;
        }
    }

    /* Finalize struct */
    if (corto_define(Point)) {
        goto error;
    }

    /* Create an instance of Point */
    corto_object p = corto_createChild(root_o, "p", Point);
    if (!p) {
        goto error;
    }

    *(corto_int32*)CORTO_OFFSET(p, x->offset) = 10;
    *(corto_int32*)CORTO_OFFSET(p, y->offset) = 20;

    printf("p = %s\n", corto_contentof(NULL, "text/corto", p));

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
