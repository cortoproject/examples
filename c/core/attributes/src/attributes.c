/* $CORTO_GENERATED
 *
 * attributes.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/attributes.h>

/* $header() */
/* attributes
 *
 * Attributes are specified at object creation, and specify what the capabilities
 * of an object will be. By limiting the amount of attributes, you can reduce
 * the memory footprint of objects.
 *
 * Available attributes are:
 * SCOPED     - object has a name and may contain child objects
 * WRITABLE   - object can be locked for writing
 * OBSERVABLE - object can be observed
 * PERSISTENT - object can be managed by a mount
 */

void printAttr(corto_object o) {
    printf("attributes of %s: ", corto_fullpath(NULL, o));
    if (corto_checkAttr(o, CORTO_ATTR_SCOPED)) printf("S");
    if (corto_checkAttr(o, CORTO_ATTR_WRITABLE)) printf("W");
    if (corto_checkAttr(o, CORTO_ATTR_OBSERVABLE)) printf("O");
    if (corto_checkAttr(o, CORTO_ATTR_PERSISTENT)) printf("P");
    if (corto_attrof(o) == 0) {
        printf("none");
    }
    printf("\n");
}
/* $end */

int attributesMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Attributes are set per thread. All objects created in a thread will be
     * created with the configured attributes specific to that thread. */

    /* Create a low-footprint object with no attributes */
    corto_attr prev = corto_setAttr(0);
    corto_int32 *i = corto_create(corto_int32_o);
    corto_setAttr(prev);

    /* Display attributes of the int32 object */
    printAttr(i);

    return 0;
/* $end */
}
