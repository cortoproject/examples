#include "subscriber_type.h"

/* subscriber_type
 *
 * This example shows basic usage of corto_subscribe to subscribe only for
 * objects of a specific type.
 */

void onNotify(
  corto_object this,
  corto_eventMask event,
  corto_result *o,
  corto_subscriber subscriber)
{
    printf("UPDATE '%s'\n", o->id);
}

int subscriber_typeMain(int argc, char *argv[]) {

    /* Create a subscriber that only subscribes for DEFINE events for objects of
     * type int32. */
    corto_subscriber s = corto_subscribe(CORTO_ON_DEFINE, "/", "*")
        .type("int32")
        .callback(onNotify);
    if (!s) {
        goto error;
    }

    /* Create object 'foo' of type int32. This will trigger the observer */
    corto_object foo = corto_createChild(root_o, "foo", corto_int32_o);
    if (!foo) {
        goto error;
    }

    /* Create object 'bar' of type float32. This won't trigger the observer */
    corto_object bar = corto_createChild(root_o, "bar", corto_float32_o);
    if (!bar) {
        goto error;
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
