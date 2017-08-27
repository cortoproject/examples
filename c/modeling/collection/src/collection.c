/* This is a managed file. Do not delete this comment. */

#include <include/collection.h>


/* This example shows how to use simple corto collections */

int collectionMain(int argc, char *argv[]) {

    /* Create new struct instance on stack */
    collection_MyCollections value;

    /* Linked lists requre initialization, so call init on struct. This will
     * create an empty list object for the 'ints' member. */
    corto_ptr_init(&value, collection_MyCollections_o);

    /* Add some values to the ints collection */
    collection_intListAppend(value.ints, 10);
    collection_intListAppend(value.ints, 20);

    /* Set the values of the floats member */
    value.floats[0] = 10.5;
    value.floats[1] = 20.5;
    value.floats[2] = 30.5;

    /* Set values of the strings member */
    corto_stringSeqSize(&value.strings, 2);
    corto_ptr_setstr(&value.strings.buffer[0], "Hello");
    corto_ptr_setstr(&value.strings.buffer[1], "World");
    /* Appending elements to a sequence is inefficient, but possible. */
    corto_stringSeqAppend(&value.strings, "Foo"); 
    corto_stringSeqAppend(&value.strings, "Bar");

    /* Print value of object */
    char *str = corto_ptr_contentof(&value, collection_MyCollections_o, "text/json");
    corto_info("value = %s", str);
    corto_dealloc(str);

    /* Deinitialize value */
    corto_ptr_deinit(&value, collection_MyCollections_o);

    return 0;
}

