#include "Select.h"

/* Demonstrates how select can be used to iteratively browse contents of the
 * Corto store */

/* Function that iterates over an iterator returned by the select call. The
 * select iterator returns objects of the type 'corto_selectItem' which do
 * not expose the object directly for performance / scalability reasons. */
void iterate(corto_iter *iter) {
    /* Iterate until select returns no more objects */
    corto_resultIterForeach(*iter, e) {
        printf("%s/%s of type %s\n",
            e.parent,
            e.name,
            e.type);
    }
}

int SelectMain(int argc, char *argv[]) {
    corto_iter iter;

    /* Create a few dummy objects to fill up the store */
    corto_voidCreateChild_auto(NULL, a);
    corto_voidCreateChild_auto(a, b);
    corto_voidCreateChild_auto(a, c);
    corto_voidCreateChild_auto(b, d);

    /* Select a single nested object */
    iter = corto_select("/", "a/b/d").iter(); iterate(&iter);

    /* Select the parent of d (b) */
    iter = corto_select("/d", "..").iter(); iterate(&iter);

    /* Select all objects in the root scope */
    iter = corto_select("/", "*").iter(); iterate(&iter);

    /* Select all descendants of a */
    iter = corto_select("/", "a//*").iter(); iterate(&iter);

    /* Select all objects in the store that start with a 'w' */
    iter = corto_select("/", "//w*").iter(); iterate(&iter);

    return 0;
}
