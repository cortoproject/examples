/* This is a managed file. Do not delete this comment. */

#include <include/list_read.h>


/* Simple demo of a mount that serves up a number of objects when queried. */

int list_readMain(int argc, char *argv[]) {

    /* Load mount configuration, data is mounted under /data */
    if (corto_load("config.json", 0, NULL)) {
        goto error;
    }

    /* Select data from the mount in JSON format */
    corto_iter it;
    if (corto_select("data/*").contentType("text/json").iter(&it)) {
        goto error;
    }

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

