/* $CORTO_GENERATED
 *
 * objects.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/objects.h>

/* $header() */
/* objects
 *
 * This example shows basic usage of core API functions to create, update
 * and delete objects.
 */

/* Callback for observer */
void onUpdate(
    corto_object this,
    corto_eventMask event,
    corto_object o,
    corto_observer observer)
{
    /* Show information about the object that triggered the observer */
    printf("update received for id='%s' parent='%s' type='%s' value='%d'\n",
      corto_idof(o),
      corto_fullpath(NULL, corto_parentof(o)),
      corto_fullpath(NULL, corto_typeof(o)),
      *corto_int32(o));
}
/* $end */

int objectsMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a signed integer object in the global object hierarchy */
    corto_int32 *i = corto_createChild(root_o, "i", corto_int32_o);
    if (!i) {
        goto error;
    }

    /* Observe the object for updates */
    corto_observer observer = corto_observe(CORTO_ON_UPDATE, i).callback(onUpdate);

    /* Change the value of the object */
    if (!corto_updateBegin(i)) {
        *i = 10;
        if (corto_updateEnd(i)) {
            goto error;
        }
    } else {
        goto error;
    }

    /* Delete the observer */
    if (corto_delete(observer)) {
        goto error;
    }

    /* Delete the object */
    if (corto_delete(i)) {
        goto error;
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
