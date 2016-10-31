#include "dynamic_collection.h"

/* dynamic_struct
 *
 * This example shows how to dynamically create a new array type.
 */

int dynamic_collectionMain(int argc, char *argv[]) {

    /* Create a new array */
    corto_array ints = corto_declareChild(root_o, "ints", corto_array_o);
    if (!ints) {
        goto error;
    }
    if (!corto_checkState(ints, CORTO_DEFINED)) {
        /* Set the element type and max size on the base collection class */
        corto_setref(&corto_collection(ints)->elementType, corto_int32_o);
        corto_collection(ints)->max = 3;
        if (corto_define(ints)) {
            goto error;
        }
    }

    /* Create instance of ints */
    corto_int32 *myArray = corto_createChild(root_o, "myArray", ints);
    if (!myArray) {
        goto error;
    }

    myArray[0] = 10;
    myArray[1] = 20;
    myArray[2] = 30;

    printf("myArray = %s\n", corto_contentof(NULL, "text/corto", myArray));

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
