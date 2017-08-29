#include <include/historyBatching.h>

int historyBatchingMain(int argc, char *argv[]) {

    /* Load mount that has sampleRate set to 1Hz */
    if (corto_load("config.json", 0, NULL)) {
        goto error;
    }

    /* Publish a new value every 1msec */
    int i = 0;
    char value[20];
    while (true) {
        sprintf(value, "%d", i ++);
        corto_publish(CORTO_UPDATE, "data/foo", "int32", "text/corto", value);
    }

    return 0;
error:
    corto_error("%s", corto_lasterr());
    return -1;
}
