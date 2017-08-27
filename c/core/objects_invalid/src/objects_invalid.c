/* $CORTO_GENERATED
 *
 * objects_invalid.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/objects_invalid.h>

/* $header() */
/* objects_invalid
 *
 * This example shows basic usage of the corto_invalidate function. This
 * function can be used to invalidate an object, which is typically used when
 * the object store is used as a cache for remote objects. By invalidating the
 * object, the application can be notified that the data has gone stale.
 */

 /* Callback for observer */
void onNotify(corto_observerEvent *e)
{
    char buff[11];
    switch(e->event) {
    case CORTO_DECLARE: strcpy(buff, "DECLARE"); break;
    case CORTO_DEFINE: strcpy(buff, "DEFINE"); break;
    case CORTO_UPDATE: strcpy(buff, "UPDATE"); break;
    case CORTO_DELETE: strcpy(buff, "DELETE"); break;
    case CORTO_INVALIDATE: strcpy(buff, "INVALIDATE"); break;
    default: 
        break;
    }
    corto_info("%s '%s'", buff, corto_idof(e->data));
}

void printValid(corto_object o) {
    /* The checkstate function can be used to check for validity */
    corto_info("object '%s' is %svalid",
      corto_idof(o),
      corto_checkState(o, CORTO_VALID) ? "" : "not ");
}
/* $end */

int objects_invalidMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a new object */
    corto_object *o = corto_createChild(root_o, "o", corto_void_o);
    if (!o) {
        goto error;
    }

    printValid(o);

    /* Create observer to observe INVALIDATE and DEFINE events */
    corto_observer observer = corto_observe(CORTO_DEFINE|CORTO_INVALIDATE, o)
      .callback(onNotify);
    if (!observer) {
        goto error;
    }

    /* Invalidate the object */
    if (corto_invalidate(o)) {
        goto error;
    }

    printValid(o);

    /* To revalidate object, we must redefine it */
    if (corto_define(o)) {
        goto error;
    }

    printValid(o);

    if (corto_delete(observer)) {
        goto error;
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
