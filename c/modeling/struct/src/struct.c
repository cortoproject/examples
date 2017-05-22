/* $CORTO_GENERATED
 *
 * struct.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/struct.h>

/* $header() */
/* Simple example that shows how to model and use a struct type. */
/* $end */

int structMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create new instance of struct type
     * 
     * The struct_Point C-type and the struct_PointCreate function are generated 
     * from the .cx file and provide a type-safe interface. 
     */
    struct_Point *p = struct_PointCreate(10, 20);
    if (!p) {
        goto error;
    }

    /* Send update notification for new value */
    struct_PointUpdate(p, 20, 30);

    /* When generating code, an application can access members natively */
    corto_info("p->x = %d, p->y = %d\n", p->x, p->y);
    corto_delete(p);


    /* It is also possible to use the dynamic API to create, update and delete
     * objects. The following code is equivalent to the above. */

    /* The struct_Point_o variable is a reference to the Point type object. This
     * type is automatically inserted before the application starts. */
    p = corto_declare(struct_Point_o);

    /* Check if object is defined, in case multiple threads are creating it */
    if (!corto_checkState(p, CORTO_DEFINED)) {
        p->x = 10;
        p->y = 20;
        if (corto_define(p)) {
            corto_delete(p);
            p = NULL;
            goto error;
        }
    }

    /* Send update notification for new value */
    if (!corto_updateBegin(p)) {
        p->x = 20;
        p->y = 30;
        if (corto_updateEnd(p)) goto error;
    } else {
        goto error;
    }

    corto_delete(p);

    return 0;
error:
    return -1;
/* $end */
}
