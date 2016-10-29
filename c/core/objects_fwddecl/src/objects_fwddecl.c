#include "objects_fwddecl.h"

/* objects_fwddecl
 *
 * This example shows basic usage of core API functions to forward declare
 * objects. If you use corto_createChild (see objects example) the object is
 * defined with a default value. As creating an object generates a DEFINE event,
 * you may want to override the default value of the object.
 *
 * Forward declarations allow you to create an object that has not yet been
 * defined. This allows you to set the value of the object before it is defined.
 *
 * Furthermore, forward declarations can be utilized to instantiate an object
 * graph that contains cycles.
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
    printf("'%s' with value '%d'\n", corto_idof(o), *(corto_int32*)o);
}

int objects_fwddeclMain(int argc, char *argv[]) {

    /* Create an observer to make the object-creation sequence visible */
    corto_observer observer = corto_observe(
        CORTO_ON_DECLARE|CORTO_ON_DEFINE|CORTO_ON_UPDATE|CORTO_ON_DELETE|CORTO_ON_SCOPE, root_o)
        .callback(onNotify);

    /* First, show creating a regular object so we can compare the sequence with
     * creating a forward declared object */
    corto_int32 *regular = corto_createChild(root_o, "regular", corto_int32_o);
    if (!regular) {
        goto error;
    }

    /* Update regular object with new value */
    if (!corto_updateBegin(regular)) {
        *regular = 10;
        if (corto_updateEnd(regular)) {
            goto error;
        }
    } else {
        goto error;
    }

    /* Delete regular object */
    if (corto_delete(regular)) {
        goto error;
    }


    /* Forward declare object */
    corto_int32 *fwddecl = corto_declareChild(root_o, "fwddecl", corto_int32_o);
    if (!fwddecl) {
        goto error;
    }

    /* This check *guarantees* that we won't overwrite the value of this object
     * if it has also been declared in another thread. */
    if (!corto_checkState(fwddecl, CORTO_DEFINED)) {
        *fwddecl = 10;

        /* Now that the value is set, we can define the object. The observer
         * will receive a DEFINE notification with the right value set. */
        if (corto_define(fwddecl)) {
            goto error;
        }
    }

    /* Updating the forward declared object works exactly the same */
    if (!corto_updateBegin(fwddecl)) {
        *fwddecl = 20;
        if (corto_updateEnd(fwddecl)) {
            goto error;
        }
    } else {
        goto error;
    }

    /* Delete fwddecl object */
    if (corto_delete(regular)) {
        goto error;
    }

    /* Delete observer */
    if (corto_delete(observer)) {
        goto error;
    }

    return 0;
error:
    return -1;
}
