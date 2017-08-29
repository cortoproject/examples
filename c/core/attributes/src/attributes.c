
#include <include/attributes.h>

/** attributes
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
    char buff[5] = {0};
    if (corto_checkAttr(o, CORTO_ATTR_NAMED)) strcat(buff, "S");
    if (corto_checkAttr(o, CORTO_ATTR_WRITABLE)) strcat(buff, "W");
    if (corto_checkAttr(o, CORTO_ATTR_OBSERVABLE)) strcat(buff, "O");
    if (corto_checkAttr(o, CORTO_ATTR_PERSISTENT)) strcat(buff, "P");
    if (corto_attrof(o) == 0) strcat(buff, "none");
    corto_info("attributes of '%s': '%s'", corto_fullpath(NULL, o), buff);
}

int attributesMain(int argc, char *argv[]) {

    /* Attributes are set per thread. All objects created in a thread will be
     * created with the configured attributes specific to that thread. */

    /* Create a low-footprint anonymous object with no attributes */
    corto_attr prev = corto_setAttr(0);
    int32_t *i = corto_create(corto_int32_o);
    corto_setAttr(prev);

    /* Display attributes of the i object */
    printAttr(i);
    corto_delete(i);

    /* Create a named observable & persistent object */
    prev = corto_setAttr(CORTO_ATTR_OBSERVABLE | CORTO_ATTR_PERSISTENT);
    int32_t *j = corto_createChild(root_o, "j", corto_int32_o);
    corto_setAttr(prev);

    /* Display attributes of the j object */
    printAttr(j);
    corto_delete(j);

    return 0;
}
