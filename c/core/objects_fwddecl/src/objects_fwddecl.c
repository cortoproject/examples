
#include <include/objects_fwddecl.h>

/* objects_fwddecl
 *
 * This example shows basic usage of core API functions to forward declare
 * objects. If you use corto_createChild (see objects example) an object is
 * declared & defined with a default value. As the DEFINE event is a 'data'
 * event that is potentially synchronized, sometimes an application wants to
 * set a custom value before defining an object. Forward declaring an object,
 * then setting the value, then defining it allows for that.
 *
 * This technique is used in (amongst others) the dynamic_struct example to first
 * declare the struct (and members) and define it when all members are created.
 *
 * Furthermore, forward declarations can be utilized to instantiate an object
 * graph declaratively that contains cycles. The word 'declaratively' is key
 * here. An application is able to create cycles imperatively by first creating
 * two objects, and then make them both point to each other. However, without
 * forward declarations, this will generate at least 4 events (create A, 
 * create B, update A, update B), and the first three events contain an 
 * 'intermediate' state that ideally is not synchronized.
 *
 * With forward declarations an application can define A and B after the cycle
 * has already been created, thus eliminating the "intermediate" state.
 */

 /* Callback for observer */
void onNotify(corto_observerEvent *e)
{
    char buff[8];
    switch(e->event) {
    case CORTO_DECLARE: strcpy(buff, "DECLARE"); break;
    case CORTO_DEFINE: strcpy(buff, "DEFINE"); break;
    case CORTO_UPDATE: strcpy(buff, "UPDATE"); break;
    case CORTO_DELETE: strcpy(buff, "DELETE"); break;
    default: break;
    }
    corto_info("%s '%s' with value '%d'", 
        buff, corto_idof(e->data), *(corto_int32*)e->data);
}

int objects_fwddeclMain(int argc, char *argv[]) {

    /* Create an observer to make the object-creation sequence visible */
    corto_observer observer = corto_observe(
        CORTO_DECLARE|CORTO_DEFINE|CORTO_UPDATE|CORTO_DELETE|CORTO_ON_SCOPE, root_o)
        .callback(onNotify);

    /* First, show creating a regular object so we can compare the sequence of
     * notifications with creating a forward declared object */
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
     * if it has also been declared in another thread. If two threads are
     * declaring the same object, one of the `corto_declareChild` functions will
     * block until the other thread has defined the object.
     *
     * This is the idiomatic, and only safe(!) way to define an object in a multi 
     * threaded application.
     */
    if (!corto_checkState(fwddecl, CORTO_VALID)) {
        *fwddecl = 10;

        /* Now that the value is set, we can define the object. The observer
         * will receive a DEFINE notification after the value is assigned. */
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
    if (corto_delete(fwddecl)) {
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
