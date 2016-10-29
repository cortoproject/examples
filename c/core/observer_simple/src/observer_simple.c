#include "observer_simple.h"

/* observer_simple
 *
 * This example shows basic usage of core API functions to observer create,
 * update and delete events of an object.
 */

 /* Callback for observer */
void onNotify(
   corto_object this,
   corto_eventMask event,
   corto_object o,
   corto_observer observer)
{
    switch(event) {
    case CORTO_ON_DECLARE: printf("DECLARE "); break;
    case CORTO_ON_DEFINE: printf("DEFINE "); break;
    case CORTO_ON_UPDATE: printf("UPDATE "); break;
    case CORTO_ON_DELETE: printf("DELETE "); break;
    default: break;
    }
    printf("'%s'\n", corto_idof(o));
}

int observer_simpleMain(int argc, char *argv[]) {

    /* Observe notifications from objects created in the root scope */
    corto_observer observer = corto_observe(
      CORTO_ON_DEFINE| /* Create notifications */
      CORTO_ON_UPDATE| /* Update notifications */
      CORTO_ON_DELETE| /* Delete notifications */
      CORTO_ON_SCOPE,  /* All objects in the scope of the observable */
      root_o)          /* root_o is the observable */
      .callback(onNotify); /* The callback function */

    /* Creating this object will create a DEFINE event */
    corto_object o = corto_createChild(root_o, "o", corto_void_o);
    if (!o) {
        goto error;
    }

    /* Update this object. Note that we use 'update' and not 'updateBegin' and
     * 'updateEnd', because the object is a void object, and void objects don't
     * have a value that needs to be locked while updating. */
    if (corto_update(o)) {
        goto error;
    }

    /* Delete the object */
    if (corto_delete(o)) {
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
