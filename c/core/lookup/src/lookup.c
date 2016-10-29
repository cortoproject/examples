#include "lookup.h"

/* lookup
 *
 * This example shows basic usage of core API functions to lookup objects in the
 * object hierarchy.
 */

int lookupMain(int argc, char *argv[]) {

    /* Create a few objects so we have something to lookup */
    corto_object tier1 = corto_createChild(root_o, "tier1", corto_void_o);
    if (!tier1) {
        goto error;
    }

    corto_object tier2 = corto_createChild(tier1, "tier2", corto_void_o);
    if (!tier2) {
        goto error;
    }

    corto_object tier3 = corto_createChild(tier2, "tier3", corto_void_o);
    if (!tier3) {
        goto error;
    }

    /* Lookup an object in the root */
    corto_object o = corto_lookup(root_o, "tier1");
    if (o) {
        printf("found object '%s'\n", corto_fullpath(NULL, o));

        /* Release the object so corto knows you no longer need it */
        corto_release(o);
    }

    /* Lookup a nested object */
    o = corto_lookup(root_o, "tier1/tier2");
    if (o) {
        printf("found object '%s'\n", corto_fullpath(NULL, o));

        /* Release the object so corto knows you no longer need it */
        corto_release(o);
    }

    /* Lookup a nested object, specify a nested 'from' scope */
    o = corto_lookup(tier1, "tier2/tier3");
    if (o) {
        printf("found object '%s'\n", corto_fullpath(NULL, o));

        /* Release the object so corto knows you no longer need it */
        corto_release(o);
    }

    /* Objects in the hierarchy are automatically deleted */

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
