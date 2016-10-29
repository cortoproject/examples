#include "Crud.h"

/* Observer callback */
void onUpdate(corto_object this, corto_eventMask mask, corto_object observable, corto_observer observer) {
    printf("%s updated with value %s\n",
        corto_idof(observable),
        corto_str(observable, 0));
}

int CrudMain(int argc, char *argv[]) {

    /* Create an object of type int32 in the root, called 'a' */
    corto_int32 *a = corto_int32CreateChild(root_o, "a", 10);

    /* Create a second object in the scope of a, called 'b' */
    corto_int32 *b = corto_int32CreateChild(a, "b", 20);

    /* Create an observer that listens for updates of 'a' */
    corto_observer observer = corto_observe(CORTO_ON_UPDATE, a)
        .callback(onUpdate);

    /* Update value of 'a'. This will notify the observer. */
    corto_int32Update(a, 11);

    /* Delete observer */
    corto_delete(observer);

    /* Delete objects */
    corto_delete(b);
    corto_delete(a);

    return 0;
}
