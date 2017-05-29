/* $CORTO_GENERATED
 *
 * subscriber_type.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/subscriber_type.h>

/* $header() */
/* subscriber_type
 *
 * This example shows basic usage of corto_subscribe to subscribe only for
 * objects of a specific type.
 */

void onNotify(corto_subscriberEvent *e)
{
    corto_info("UPDATE '%s'", e->data.id);
}
/* $end */

int subscriber_typeMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a subscriber that subscribes for events for objects of type int32. */
    corto_subscriber s = corto_subscribe("*")
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
/* $end */
}
