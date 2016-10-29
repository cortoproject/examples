#include "observer_type.h"


/* observer_type
 *
 * This example shows how to create an observer that filters objects of a
 * specified type.
 */

 /* Callback for observer */
void onNotify(
   corto_object this,
   corto_eventMask event,
   corto_object o,
   corto_observer observer)
{
    printf("trigger for %s\n", corto_idof(o));
}

int observer_typeMain(int argc, char *argv[]) {

    /* Observe notifications only for objects of the int32 type */
    corto_observer observer = corto_observe(CORTO_ON_DEFINE|CORTO_ON_SCOPE, root_o)
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
}
