#include "objects_invalid.h"

/* objects_invalid
 *
 * This example shows basic usage of the corto_invalidate function. This
 * function can be used to invalidate an object, which is typically used when
 * the object store is used as a cache for remote objects. By invalidating the
 * object, the application can be notified that the data has gone stale.
 */

 /* Callback for observer */
void onNotify(
   corto_object this,
   corto_eventMask event,
   corto_object o,
   corto_observer observer)
{
    switch(event) {
    case CORTO_ON_DEFINE: printf("DEFINE "); break;
    case CORTO_ON_INVALIDATE: printf("INVALIDATE "); break;
    default: return;
    }
    printf("'%s'\n", corto_idof(o));
}

void printValid(corto_object o) {
    /* The checkstate function can be used to check for validity */
    printf("object '%s' is %svalid\n",
      corto_idof(o),
      corto_checkState(o, CORTO_VALID) ? "" : "not ");
}

int objects_invalidMain(int argc, char *argv[]) {

    /* Create a new object */
    corto_object *o = corto_createChild(root_o, "o", corto_void_o);
    if (!o) {
        goto error;
    }

    printValid(o);

    /* Create observer to observe INVALIDATE and DEFINE events */
    corto_observer observer = corto_observe(CORTO_ON_DEFINE|CORTO_ON_INVALIDATE, o)
      .callback(onNotify);
    if (!observer) {
        goto error;
    }

    /* Invalidate the object */
    if (corto_invalidate(o)) {
        goto error;
    }

    printValid(o);

    /* To revalidate object, we must redefine it */
    if (corto_define(o)) {
        goto error;
    }

    printValid(o);

    if (corto_delete(observer)) {
        goto error;
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
