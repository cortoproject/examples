/* $CORTO_GENERATED
 *
 * mount_read.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/mount_read.h>

/* $header() */
/* Simple demo of a mount that serves up a number of objects when queried. */
/* $end */

int mount_readMain(int argc, char *argv[]) {
/* $begin(main) */

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
/* $end */
}
