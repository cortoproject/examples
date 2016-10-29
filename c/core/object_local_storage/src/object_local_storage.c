#include "object_local_storage.h"

/* object_local_storage
 *
 * This example shows how you can attach userdata to an object after it has been
 * created.
 */

void myDestructor(void *value) {
    printf("myDestructor called\n");
    free(value);
}

int object_local_storageMain(int argc, char *argv[]) {

    /* Create an object to experiment on */
    corto_object o = corto_createChild(root_o, "o", corto_void_o);
    if (!o) {
        goto error;
    }

    /* Generate a unique ols key. These keys guarantee that multiple components
     * can attach userdata to an object without getting in each others way.
     *
     * The destructor is called when the object is deleted, and is useful when
     * the data you attached needs to be cleaned up.
     */
    corto_uint8 myKey = corto_olsKey(myDestructor);

    /* Attach a value to the object */
    corto_olsSet(o, myKey, strdup("Hello World"));

    /* Read the value */
    printf("ols value for myKey: '%s'\n", (char*)corto_olsGet(o, myKey));

    /* Delete the object */
    if (corto_delete(o)) {
        goto error;
    }

    return 0;
error:
    return -1;
}
