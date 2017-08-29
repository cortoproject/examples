
#include <include/dynamic_struct.h>

/** dynamic_struct
 *
 * This example shows how to dynamically create a new struct type.
 */

int dynamic_structMain(int argc, char *argv[]) {

    /* Create a new struct */
    corto_struct Point = corto_declareChild(root_o, "Point", corto_struct_o);
        if (!Point) goto error;

        /* Create x member */
        corto_member x = corto_declareChild(Point, "x", corto_member_o);
            if (!x) goto error;
            corto_ptr_setref(&x->type, corto_int32_o);
            if (corto_define(x)) goto error;

        /* Create y member */
        corto_member y = corto_declareChild(Point, "y", corto_member_o);
            if (!y) goto error;
            corto_ptr_setref(&y->type, corto_int32_o);
            if (corto_define(y)) goto error;

        /* Finalize struct */
        if (corto_define(Point)) goto error;

    /* Create a heap segment large enough for Point */
    void *p = corto_ptr_new(Point);
    if (!p) {
        goto error;
    }

    /* Use dynamic corto_value API to set member dynamically */
    corto_value p_value = corto_value_value(p, Point);
    corto_value x_member;
    if (corto_value_memberExpr(&p_value, "x", &x_member)) {
        goto error;
    }
    *(int32_t*)corto_value_ptrof(&x_member) = 10;

    /* Use calculated member offset to set value */
    *(corto_int32*)CORTO_OFFSET(p, y->offset) = 20;

    corto_info("p = %s", corto_value_contentof(&p_value, "text/corto"));

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
