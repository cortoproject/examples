#include "Select.h"

/* Demonstrates how select can be used to iteratively browse contents of the 
 * Corto store */

/* Function that iterates over an iterator returned by the select call. The 
 * select iterator returns objects of the type 'corto_selectItem' which do
 * not expose the object directly for performance / scalability reasons. */
void iterate(corto_iter *iter) {
    /* Iterate until select returns no more objects */
    while (corto_iterHasNext(iter)) {
        corto_selectItem *item = corto_iterNext(iter);
        printf("%s/%s of type %s\n",
            item->parent,
            item->name,
            item->type);
    }
}

int SelectMain(int argc, char *argv[]) {
    corto_iter iter;

    /* Create a few dummy objects to fill up the store */
    corto_int32 *a = corto_voidCreateChild(NULL, "a");
    corto_int32 *b = corto_voidCreateChild(a, "b");
    corto_voidCreateChild(a, "c");
    corto_int32 *d = corto_voidCreateChild(b, "d");

    /* Select a single nested object */
    corto_select(root_o, "a/b/d", &iter); iterate(&iter);
    
    /* Select the parent of d (b) */
    corto_select(d, "..", &iter); iterate(&iter);

    /* Select all objects in the root scope */
    corto_select(root_o, "*", &iter); iterate(&iter);

    /* Select all descendants of a */
    corto_select(root_o, "a//*", &iter); iterate(&iter);

    /* Select all objects in the store that start with a 'w' */
    corto_select(root_o, "//w*", &iter); iterate(&iter);

    return 0;
}
