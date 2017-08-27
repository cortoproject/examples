/* $CORTO_GENERATED
 *
 * observer_simple.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/observer_simple.h>

/* $header() */
/* observer_simple
 *
 * This example shows basic usage of core API functions to observer create,
 * update and delete events of an object.
 */

 /* Callback for observer */
void onNotify(corto_observerEvent *e)
{
    char buff[9];
    switch(e->event) {
    case CORTO_DECLARE: strcpy(buff, "DECLARE"); break;
    case CORTO_DEFINE: strcpy(buff, "DEFINE"); break;
    case CORTO_UPDATE: strcpy(buff, "UPDATE"); break;
    case CORTO_DELETE: strcpy(buff, "DELETE"); break;
    default: break;
    }
    corto_info("%s '%s'", buff, corto_idof(e->data));
}
/* $end */

int observer_simpleMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Observe notifications from objects created in the root scope */
    corto_observer observer = corto_observe(
      CORTO_DEFINE| /* Create notifications */
      CORTO_UPDATE| /* Update notifications */
      CORTO_DELETE| /* Delete notifications */
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
/* $end */
}
