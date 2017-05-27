/* $CORTO_GENERATED
 *
 * mount_simple.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/mount_simple.h>

/* $header() */
/* $end */

int mount_simpleMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a demo mount instance, mount data under '/data' */
    if (!mount_simple_DemoMountCreateChild(root_o, "myMount", "/data")) {
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
