
#include <include/subscriber_simple.h>

/* subscriber_simple
 *
 * This example shows basic usage corto_subscribe to to subscribe for create,
 * update and delete events of objects.
 *
 * The corto_subscribe API is more powerful version of corto_observe. Because it
 * does not rely on having objects in an object store, it is a better fit for
 * dealing with large datasets.
 *
 * corto_subscribe utilizes the same identifier expressions as used by
 * corto_select. For examples of identifier expressions, see the identifier_expr
 * example.
 */

void onNotify(corto_subscriberEvent *e)
{
    char buff[9];
    switch(e->event) {
    case CORTO_DEFINE: strcpy(buff, "DEFINE"); break;
    case CORTO_UPDATE: strcpy(buff, "UPDATE"); break;
    case CORTO_DELETE: strcpy(buff, "DELETE"); break;
    default: break;
    }
    corto_info("%s '%s' (parent = '%s', type = '%s')", 
        buff, e->data.id, e->data.parent, e->data.type);
}

int subscriber_simpleMain(int argc, char *argv[]) {

    /* Create a subscriber that listens to create, update and delete events for
     * all objects in the 'foo' scope. */
    corto_subscriber s = corto_subscribe("foo/*")
        .callback(onNotify);
    if (!s) {
        goto error;
    }

    /* Create the 'foo' object. This will not trigger the subscriber */
    corto_object foo = corto_createChild(root_o, "foo", corto_void_o);
    if (!foo) {
        goto error;
    }

    /* Create a 'bar' object in the scope of 'foo'. This will trigger the
     * subscriber with a DEFINE event */
     corto_object bar = corto_createChild(foo, "bar", corto_void_o);
     if (!bar) {
         goto error;
     }

     /* Update 'bar'. This will trigger the subscriber with an UPDATE event */
     if (corto_update(bar)) {
        goto error;
     }

     /* Delete 'bar'. This will trigger the subscriber with a DELETE event */
     if (corto_delete(bar)) {
        goto error;
     }

     /* The following calls to corto_publish demonstrate how a subscriber can
      * receive notifications from objects that aren't physically located in the
      * object store. */

     /* Publish a DEFINE for an object */
     if (corto_publish(CORTO_DEFINE, "/foo/zoo", "int32", "text/corto", "10")) {
        goto error;
     }

     /* Publish an UPDATE for an object */
     if (corto_publish(CORTO_UPDATE, "/foo/zoo", "int32", "text/corto", "20")) {
        goto error;
     }

     /* Publish a DELETE for an object */
     if (corto_publish(CORTO_DELETE, "/foo/zoo", "int32", NULL, NULL)) {
        goto error;
     }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
