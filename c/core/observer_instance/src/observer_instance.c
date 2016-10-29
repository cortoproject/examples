#include "observer_instance.h"

/* observer_instance
 *
 * This example shows using a mechanism that allows an application to filter out
 * events that it has created itself. A typical application is a class that is
 * observing itself, and has a method that is updating its own value. It is often
 * undesirable that the instance receives back its own update.
 *
 * The underlying mechanism is called 'ownership' and is used extensively (yet
 * often invisible) throughout the core API to do a wide range of things from
 * preventing multiple apps from writing to the same resource, bridging of data
 * between connectors and, as mentioned, filter out your own events.
 *
 * This application shows only the most basic usage of ownership.
 */

 /* Callback for observer */
void onNotify(
   corto_object this, /* This is the instance passed to corto_observe */
   corto_eventMask event,
   corto_object o,
   corto_observer observer)
{
    printf("this = '%s', update '%s'\n", corto_idof(this), corto_idof(o));
}

int observer_instanceMain(int argc, char *argv[]) {

    /* Create an object that will be the instance we associate with our observer.
     * Updates "from this instance" will not trigger the observer. */
    corto_object myInstance = corto_createChild(root_o, "instance", corto_void_o);
    if (!myInstance) {
        goto error;
    }

    /* Create an observable object */
    corto_object observable = corto_createChild(root_o, "observable", corto_void_o);
    if (!observable) {
        goto error;
    }

    /* Create an observer that is associated with the instance */
    corto_observer observer = corto_observe(CORTO_ON_UPDATE, observable)
      .instance(myInstance)  /* The instance associated with the observer */
      .callback(onNotify);

    /* Update the observable. The observer will be triggered */
    if (corto_update(observable)) {
        goto error;
    }

    /* Set the "owner" to our instance */
    corto_object prev = corto_setOwner(myInstance);

    /* Update the observable again. Because the owner is set to myInstance, and
     * the observer is associated with myInstance, this update will not trigger
     * the observer. */
    if (corto_update(observable)) {
       goto error;
    }

    /* Restore the owner (important!) */
    corto_setOwner(prev);

    /* Delete observer */
    if (corto_delete(observer)) {
        goto error;
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
