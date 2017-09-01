
#include <include/objects.h>

/* objects
 *
 * This example shows basic usage of core API functions to create, update
 * and delete objects.
 */

/* Callback for observer */
void onUpdate(corto_observerEvent *e)
{
    /* Show information about the object that triggered the observer */
    corto_info("update received for id='%s' parent='%s' type='%s' value='%d'",
      corto_idof(e->data),
      corto_fullpath(NULL, corto_parentof(e->data)),
      corto_fullpath(NULL, corto_typeof(e->data)),
      *corto_int32(e->data));
}

int objectsMain(int argc, char *argv[]) {

    /* Create a signed integer object in the global object hierarchy */
    int32_t *i = corto_createChild(root_o, "i", corto_int32_o);
    if (!i) {
        goto error;
    }

    /* Observe the object for updates */
    corto_observer observer = corto_observe(CORTO_UPDATE, i).callback(onUpdate);

    /* Change the value of the object */
    if (!corto_update_begin(i)) {
        *i = 10;
        if (corto_update_end(i)) {
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
}
