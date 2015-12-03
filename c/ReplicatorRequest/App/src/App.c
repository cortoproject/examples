#include "App.h"

int AppMain(int argc, char *argv[]) {
    corto_resultIter iter;

    /* Create a scope which will hold a list of car brands */
    corto_object Cars_o = corto_voidCreateChild(root_o, "Cars");

    /* Create the CarBrands replicator on the Cars scope */
    Replicator_CarBrands r = Replicator_CarBrandsCreate(Cars_o);

    /* Select all contents of the Cars scope */
    corto_select(root_o, "Cars/*", &iter);

    /* Iterate over the results */
    corto_resultIterForeach(iter, e) {
        printf("Found %s of type '%s'\n", e.name, e.type);
    }

    /* Cleanup replicator */
    corto_delete(r);

    return 0;
}
