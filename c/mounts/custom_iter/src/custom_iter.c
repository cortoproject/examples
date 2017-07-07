/* This is a managed file. Do not delete this comment. */

#include <include/custom_iter.h>


/* This example demonstrates a mount with a custom iterator implementation. This
 * allows a mount maximum flexibility over how much data is loaded into memory
 * for a single request, as corto will request new results from the mount as the
 * application is iterating through the results.
 *
 * Using custom iterators is recommended practice for any mount that potentially
 * mounts large datasets. */

int custom_iterMain(int argc, char *argv[]) {

    if (corto_load("config.json", 0, NULL)) {
        goto error;
    }

    /* Walk over data mounted under 'data' */
    corto_iter it;
    corto_select("data/*").contentType("text/json").iter(&it);

    while (corto_iter_hasNext(&it)) {
        corto_result *r = corto_iter_next(&it);
        corto_info(
            "got '%s' with type '%s' and value %s",
            r->id,
            r->type,
            corto_result_getText(r));
    }

    return 0;
error:
    corto_error("%s", corto_lasterr());
    return -1;
}

