
#include <include/objects_hierarchy.h>

/* objects_hierarchy
 *
 * This example shows basic usage of core API functions to create, update
 * and delete objects in a hierarchy.
 */

void printInfo(corto_object o) {
    corto_info("object '%s' created with parent='%s', type='%s'",
      corto_fullpath(NULL, o),
      corto_fullpath(NULL, corto_parentof(o)),
      corto_fullpath(NULL, corto_typeof(o)));
}

int objects_hierarchyMain(int argc, char *argv[]) {

    /* Create an object in the global object hierarchy */
    corto_object *parent = corto_createChild(root_o, "parent", corto_void_o);
    if (!parent) {
        goto error;
    }

    /* Show information about the parent object */
    printInfo(parent);

    /* Create an object in the scope of the parent object */
    corto_object *child = corto_createChild(parent, "child", corto_void_o);
    if (!parent) {
        goto error;
    }

    /* Show information about the child object */
    printInfo(child);

    /* Delete both the parent and child object */
    if (corto_delete(parent)) {
        goto error;
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
