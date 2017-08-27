/* $CORTO_GENERATED
 *
 * json.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/json.h>

/* $header() */
/* json
 *
 * This example shows how to write applications that just use JSON to create,
 * read, update and delete objects.
 *
 * The example also shows how to create a struct with nothing more than the core
 * API. There are easier ways to accomplish this with definition files and the
 * c-binding. See the c-binding examples for more details.
 */

 /* Callback for subscriber */
void onNotify(corto_subscriberEvent *e)
{
    corto_info("update '%s', value = %s", e->data.id, corto_result_getText(&e->data));
}
/* $end */

int jsonMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a subscriber that listens to create, update and delete events for
     * an object called 'p'. The subscriber specifies JSON as the contentType
     * which means that all notifications will be delivered as JSON. */
    corto_subscriber s = corto_subscribe("p")
        .contentType("text/json")
        .callback(onNotify);

    /* Create a Point type, so we have something to serialize to JSON (same code
     * as from dynamic_struct example) */
    corto_struct Point = corto_declareChild(root_o, "Point", corto_struct_o);
        if (!Point) goto error;

        /* Create x member */
        corto_member x = corto_declareChild(Point, "x", corto_member_o);
            if (!x) goto error;
            corto_ptr_setref(&x->type, corto_int32_o);
            if (corto_define(x)) goto error;

        /* Create y member */
        corto_member y = corto_declareChild(Point, "y", corto_member_o);
            if (!y) goto error;
            corto_ptr_setref(&y->type, corto_int32_o);
            if (corto_define(y)) goto error;

        /* Finalize struct */
        if (corto_define(Point)) goto error;


    /* Create an instance of Point. This will notify the observer with default
     * values for Point (x = 0, y = 0) */
    corto_object p = corto_createChild(root_o, "p", Point);
    if (!p) {
        goto error;
    }

    /* Update the object using corto_publish with JSON content */
    if (corto_publish(
        CORTO_UPDATE,
        "/p",         /* The object id */
        "Point",      /* The object type */
        "text/json",  /* The contentType */
        "{\"x\":10, \"y\":20}")) /* The content */
    {
        goto error;
    }

    /* Just because we can, change the values on the p object, and show that it
     * is also serialized to JSON when delivered to the subscriber */
    if (!corto_updateBegin(p)) {
        *(corto_int32*)CORTO_OFFSET(p, x->offset) = 20;
        *(corto_int32*)CORTO_OFFSET(p, y->offset) = 30;
        if (corto_updateEnd(p)) {
            goto error;
        }
    } else {
        goto error;
    }

    /* Delete subscriber */
    corto_delete(s);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
