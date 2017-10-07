#include <include/router.h>

const corto_string ROUTER_CONFIG = "config.json";

int routerMain(int argc, char *argv[]) {

    int ret = corto_load(ROUTER_CONFIG, 0, NULL);
    if (ret != 0) {
        corto_error("Failed to load [%s] Return Code [%d] Errror [%s]",
            ROUTER_CONFIG, ret, corto_lasterr());
        return -1;
    }

    corto_info("Router Initialized.");

    while (true)
    {
        usleep(1000);
    }

    return 0;
}
