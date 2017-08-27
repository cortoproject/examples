/* $CORTO_GENERATED
 *
 * observer_type.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/observer_type.h>

/* $header() */
/* observer_type
 *
 * This example shows how to create an observer that filters objects of a
 * specified type.
 */

 /* Callback for observer */
void onNotify(corto_observerEvent *e)
{
    corto_info("trigger for '%s'", corto_idof(e->data));
}
/* $end */

int observer_typeMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Observe notifications only for objects of the int32 type */
    corto_observer observer = corto_observe(CORTO_DEFINE|CORTO_ON_SCOPE, root_o)
      .type("int32")
      .callback(onNotify);

    /* This object will trigger the observable, because it is of the int32 type */
    corto_object int32object = corto_createChild(root_o, "int32object", corto_int32_o);
    if (!int32object) {
        goto error;
    }

    /* This object will not trigger the observer because it is of another type */
    corto_object float32object = corto_createChild(root_o, "float32object", corto_float32_o);
    if (!float32object) {
        goto error;
    }

    /* Delete observer */
    if (corto_delete(observer)) {
        goto error;
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
