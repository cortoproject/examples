#include <include/batching.h>

int batchingMain(int argc, char *argv[]) {
    
    /* Load mount that has sampleRate set to 1Hz */
    if (corto_load("config.json", 0, NULL)) {
        goto error;
    }

    /* Publish a new value every 1msec */
    while (true) {
        corto_publish(CORTO_UPDATE, "data/foo", "int32", "text/corto", "10");
        corto_publish(CORTO_UPDATE, "data/bar", "int32", "text/corto", "20");
        corto_publish(CORTO_UPDATE, "data/hello", "float32", "text/corto", "10.5");
        corto_publish(CORTO_UPDATE, "data/world", "float32", "text/corto", "12.5");
        corto_sleep(0, 1000000);
    }

    return 0;
error:
    corto_error("%s", corto_lasterr());
    return -1;
}
