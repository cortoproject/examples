#include "App.h"

int AppMain(int argc, char *argv[]) {

    /* Create a scope which will hold a list of car brands */
    corto_voidCreateChild_auto(root_o, Cars);

    /* Register a CarBrands mount with the 'Cars' scope */
    CarBrands_ConnectorCreate_auto(r, Cars);

    /* Select all contents of the 'Cars' scope */
    corto_iter it = corto_select("/", "Cars/*").iter(NULL);

    /* Iterate over the select results */
    corto_resultIterForeach(it, e) {
        printf("Found %s of type '%s'\n", e.name, e.type);
    }

    /* Cleanup mount */
    corto_delete(r);

    return 0;
}
