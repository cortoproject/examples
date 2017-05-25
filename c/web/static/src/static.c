/* $CORTO_GENERATED
 *
 * static.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/static.h>

/* $header() */
/* Enter code outside of main here. */
/* $end */

int staticMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a service on port 8000 that serves up index.html */
    server_Files s = server_FilesCreate(8000, "", ".");
    if (!s) {
        goto error;
    }

    /* Keep server alive */
    while (1) {
        corto_sleep(1, 0);
    }

    return 0;
error:
    corto_error("static: %s", corto_lasterr());
    return -1;
/* $end */
}
