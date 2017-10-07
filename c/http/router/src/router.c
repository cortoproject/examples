/* This is a managed file. Do not delete this comment. */

#include <router/router.h>

const corto_string ROUTER_CONFIG = "install-api.json";

int loadConfig(void);

int routerMain(int argc, char *argv[]) {

    if (loadConfig() != 0)
    {
        return -1;
    }

    while (true)
    {
        usleep(1000);
    }

    return 0;
}

int loadConfig(void) {
    corto_string path = corto_asprintf("%s/%s",
                                       CORTO_EXAMPLES_C_HTTP_ROUTER_ETC,
                                       ROUTER_CONFIG);
    if (path != NULL) {
        if (corto_load(path, 0, NULL)) {
            goto error;
        }
        else {
            corto_info("Successfully loaded config [%s]", path);
        }
        corto_dealloc(path);
    }

    return 0;

error:
    if (path != NULL) {
        corto_error("Failed to load [%s] - Error [%s]", path, corto_lasterr());
        corto_dealloc(path);
    }
    return -1;
}
