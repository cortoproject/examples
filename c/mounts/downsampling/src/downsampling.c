/* $CORTO_GENERATED
 *
 * downsampling.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/downsampling.h>

/* $header() */
/* Enter code outside of main here. */
/* $end */

int downsamplingMain(int argc, char *argv[]) {
/* $begin(main) */
    
    /* Load mount that has sampleRate set to 1Hz */
    if (corto_load("config.json", 0, NULL)) {
        goto error;
    }

    /* Publish a new value every 1msec */
    while (true) {
        corto_publish(CORTO_ON_UPDATE, "data/foo", "int32", "text/corto", "10");
        corto_sleep(0, 1000000);
    }

    return 0;
error:
    corto_error("%s", corto_lasterr());
    return -1;
/* $end */
}
