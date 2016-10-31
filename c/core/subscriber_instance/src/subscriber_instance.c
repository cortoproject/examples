#include "subscriber_instance.h"

/* subscriber_simple
 *
 * This example shows basic usage of corto_subscribe to use one instance that
 * notifies multiple instances.
 *
 * This feature is typically used when a subscriber is part of a class, and the
 * subscriber needs to notify each instance of that class individually.
 */

void onNotify(
  corto_object this,
  corto_eventMask event,
  corto_result *o,
  corto_subscriber subscriber)
{
    printf("%s: UPDATE '%s'\n", corto_idof(this), o->id);
}

int subscriber_instanceMain(int argc, char *argv[]) {

    /* Create a subscriber that is created disabled. This will give us the
     * opportunity to subscribe it for multiple instances. */
    corto_subscriber s = corto_subscribe(
        CORTO_ON_UPDATE, "/", "*")
        .disabled()
        .callback(onNotify);
    if (!s) {
        goto error;
    }

    /* Create instance 1 */
    corto_object instance1 = corto_createChild(root_o, "instance1", corto_void_o);
    if (!instance1) {
        goto error;
    }

    /* Create instance 2 */
    corto_object instance2 = corto_createChild(root_o, "instance2", corto_void_o);
    if (!instance2) {
        goto error;
    }

    /* Subscribe for instance1 */
    if (corto_subscriber_subscribe(s, instance1)) {
        goto error;
    }

    /* Subscribe for instance2 */
    if (corto_subscriber_subscribe(s, instance2)) {
        goto error;
    }

    /* Create object 'foo' */
    corto_object foo = corto_createChild(root_o, "foo", corto_void_o);
    if (!foo) {
        goto error;
    }

    /* Update will trigger subscriber twice, once for each instance */
    if (corto_update(foo)) {
        goto error;
    }

    /* Unsubscribe */
    if (corto_subscriber_unsubscribe(s, instance1)) {
        goto error;
    }
    if (corto_subscriber_unsubscribe(s, instance2)) {
        goto error;
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
