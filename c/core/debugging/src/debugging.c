#include "debugging.h"


/* dynamic_call
 *
 * This example shows how to enable debugging information. The example will
 * perform a few actions to show what kind of information is logged to the
 * console.
 */

void onUpdate(
  corto_object this,
  corto_eventMask mask,
  corto_object observable,
  corto_observer observer)
{
    printf("update received for '%s'\n", corto_idof(observable));
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
    corto_observer observer = corto_observe(CORTO_ON_UPDATE, i).callback(onUpdate);
    if (!observer) {
        goto error;
    }

    /* Notify observer- will log debugging information */
    if (!corto_updateBegin(i)) {
        *i = 10;
        if (corto_updateEnd(i)) {
            goto error;
        }
    } else {
        goto error;
    }

    /* When in debugging mode, every corto_seterr() will be printed to the
     * console */
    corto_seterr("this will be printed to the console with a stack trace");
    corto_lasterr(); /* 'catch' the error, otherwise it's printed again */

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
