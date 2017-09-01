
#include <include/debugging.h>

/** dynamic_call
 *
 * This example shows how to enable debugging information. The example will
 * perform a few actions to show what kind of information is logged to the
 * console.
 */

void onUpdate(corto_observerEvent *e)
{
    corto_info("update received for '%s'", corto_idof(e->data));
}

int debuggingMain(int argc, char *argv[]) {

    /* This enables logging of debugging information */
    corto_verbosity(CORTO_DEBUG);

    /* Perform some actions to see debugging information */
    corto_debug("Creating object...");
    corto_int32 *i = corto_createChild(root_o, "i", corto_int32_o);
    if (!i) {
        goto error;
    }

    /* Create observer */
    corto_debug("Creating observer...");
    corto_observer observer = corto_observe(CORTO_UPDATE, i).callback(onUpdate);
    if (!observer) {
        goto error;
    }

    /* Notify observer- will log debugging information */
    if (!corto_update_begin(i)) {
        *i = 10;
        if (corto_update_end(i)) {
            goto error;
        }
    } else {
        goto error;
    }

    /* When in debugging mode, every corto_seterr() will be printed to the
     * console */
    corto_seterr("this will be printed to the console with a stack trace");
    corto_lasterr(); /* read error, otherwise it is logged as uncatched */

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
