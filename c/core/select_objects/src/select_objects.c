#include "select_objects.h"

int select_objectsMain(int argc, char *argv[]) {
    corto_loaderCreate();
    
    corto_iter it;
    corto_select("/corto", "*").iterObjects(&it);

    corto_objectIterForeach(it, o) {
        printf("%s\n", corto_idof(o));
    }

    return 0;
}
