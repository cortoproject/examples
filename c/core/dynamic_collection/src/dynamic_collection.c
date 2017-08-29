#include <include/dynamic_collection.h>

/** dynamic_struct
 *
 * This example shows how to dynamically create a new array type.
 */

int dynamic_collectionMain(int argc, char *argv[]) {

    /* Create a new array */
    corto_array intArray = corto_declare(corto_array_o);
    if (!intArray) {
        goto error;
    }

    /* Set the element type and max size on the base collection class */
    corto_ptr_setref(&corto_collection(intArray)->elementType, corto_int32_o);
    corto_collection(intArray)->max = 3;
    if (corto_define(intArray)) {
        goto error;
    }

    /* Note that a shorter version of the above would be to use corto_resolve to
     * create an anonymous type, but for sake of demonstration, it is done 
     * manually. To create the same array type with corto_resolve, do: 
     * corto_resolve(NULL, "array{int32, 3}")
     */

    /* Create instance of intArray */
    int32_t myArray[3];

    myArray[0] = 10;
    myArray[1] = 20;
    myArray[2] = 30;

    char *str = corto_ptr_contentof(myArray, intArray, "text/corto");
    corto_info("myArray = '%s'", str);
    corto_dealloc(str);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
