#include "Crud.h"

/* Observer callback */
CORTO_OBSERVER(onUpdate) {
    printf("%s updated with value %s\n",
        corto_nameof(observable),
        corto_str(observable, 0));
}

int CrudMain(int argc, char *argv[]) {

    /* Create an object of type int32 in the root, called 'a' */
    corto_int32 *a = corto_int32CreateChild(root_o, "a", 10);

    /* Create a second object in the scope of a, called 'b' */
    corto_int32 *b = corto_int32CreateChild(a, "b", 20);

    /* Create an observer that listens for updates of 'a' */
    corto_observer observe = corto_observerCreate(
        CORTO_ON_UPDATE, /* We're interested in object updates */
        a, /* Listen to updates of only 'a' */
        onUpdate /* Callback to observer implementation */
    );

    /* Update value of 'a'. This will notify the observer. */
    corto_int32Update(a, 11);

    /* Delete observer */
    corto_delete(observe);

    /* Delete objects */
    corto_delete(b);
    corto_delete(a);

    return 0;
}
