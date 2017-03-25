/* $CORTO_GENERATED
 *
 * ownership.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/ownership.h>

/* $header() */
/* ownership
 *
 * Ownership is a simple mechanism where each object has an 'owner', which
 * represents the source of an object. Typically, the source of an object is a
 * mount (connector). For example, if an object has been inserted into the store
 * by a mysql connector, the owner will be the mysql connector object.
 *
 * Corto uses ownership in many ways to ensure the correct and seamless distribution
 * of data between different connectors. A few examples:
 * - Prevent updates from sources that are not the owner of an object
 * - Prevent delivering notifications from an owner to the owner (feedback)
 * - Forward method calls to the process that owns the object (RMI)
 * - Set 'target' or 'actual', based on who is updating a target object
 * - Determine whether objects are remote, and should be cached
 *
 * To ensure that all these mechanisms work smoothly, it is important that code
 * written for corto implements ownership correctly. While application developers
 * will rarely (if ever) see ownership in practice, it is an important concept
 * to understand for connector developers.
 *
 * This example creates two dummy mounts (connectors) that will both own one object.
 * The example demonstrates that when mount A updates its object, only mount B
 * will receive an update, and vice versa. In addition, the application will also
 * create an object it owns, which when updated triggers both mounts.
 *
 * The example creates a mount class with just the Core API. There are easier
 * ways to accomplish this with definition files and the c-binding. See the
 * c-binding examples for more details.
 */

void onNotify(corto_mount this, corto_eventMask event, corto_result *object) {
    if (event == CORTO_ON_UPDATE) {
        printf(" => %s: received update for '%s'\n", corto_idof(this), object->id);
    }
}
/* $end */

int ownershipMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a mount class */
    corto_class myMount = corto_declareChild(root_o, "MyMount", corto_class_o);
    if (!myMount) {
        goto error;
    }

    if (!corto_checkState(myMount, CORTO_DEFINED)) {
        /* Inherit from the corto mount class */
        corto_setref(&corto_interface(myMount)->base, corto_mount_o);

        /* Create onNotify method (called when the mount receives an update) */
        corto_method onNotifyMethod = corto_declareChild(
            myMount,
            "onNotify(core/eventMask event,core/result object)",
            corto_method_o);
        if (!onNotifyMethod) {
            goto error;
        }

        if (!corto_checkState(onNotifyMethod, CORTO_DEFINED)) {
            corto_function(onNotifyMethod)->kind = CORTO_PROCEDURE_CDECL;
            corto_function(onNotifyMethod)->fptr = (corto_word)onNotify;
            if (corto_define(onNotifyMethod)) {
                goto error;
            }

            /* Finalize class */
            if (corto_define(myMount)) {
                goto error;
            }
        }
    }

    /* Create a new object which will act as the "mount point" for both mounts.
     * The mounts will automatically subscribe for updates from this object. */
    corto_object mount = corto_createChild(root_o, "mount", corto_void_o);
    if (!mount) {
        goto error;
    }

    /* Create two instances of the mount class.  */
    corto_mount connectorA = corto_declareChild(root_o, "connectorA", myMount);
    if (!connectorA) {
        goto error;
    }

    /* Mount connectorA on /mount */
    if (!corto_checkState(connectorA, CORTO_DEFINED)) {
        /* Set 'parent' member of the baseclass of mount (subscriber) */
        corto_setstr(&corto_subscriber(connectorA)->parent, "/mount");
        if (corto_define(connectorA)) {
            goto error;
        }
    }

    corto_mount connectorB = corto_declareChild(root_o, "connectorB", myMount);
    if (!connectorB) {
        goto error;
    }

    /* Also mount connectorB on /mount */
    if (!corto_checkState(connectorB, CORTO_DEFINED)) {
        /* Set 'parent' member of the baseclass of mount (subscriber) */
        corto_setstr(&corto_subscriber(connectorB)->parent, "/mount");
        if (corto_define(connectorB)) {
            goto error;
        }
    }

    /* The corto_setOwner call sets the owner for the current thread. First we'll
     * set the owner to mountA. The object that is subsequently created will be
     * owned by connectorA */
    corto_setOwner(connectorA);

    /* Create an object that is owned by connectorA */
    corto_object *a = corto_createChild(mount, "a", corto_void_o);
    if (!a) {
        goto error;
    }

    /* Show that the owner of a is connectorA */
    printf("The owner of a = '%s'\n", corto_idof(corto_ownerof(a)));

    /* Now we'll set the owner to mountB and create another object */
    corto_setOwner(connectorB);

    corto_object *b = corto_createChild(mount, "b", corto_void_o);
    if (!b) {
        goto error;
    }

    /* Show that the owner of b is connectorB */
    printf("The owner of b = '%s'\n", corto_idof(corto_ownerof(b)));

    /* Set ownership to no owner (this application) */
    corto_setOwner(NULL);

    /* Create an application owned object */
    corto_object *c = corto_createChild(mount, "c", corto_void_o);
    if (!c) {
        goto error;
    }

    /* Show that the owner of c is null */
    printf("The owner of c = %p\n", corto_ownerof(c));

    /* Now update the objects from their respective owners. This will trigger all
     * observers but the one from the current owner. */

    printf("Update object 'a' from 'connectorA'\n");
    corto_setOwner(connectorA);
    if (corto_update(a)) {
        goto error;
    }

    printf("Update object 'b' from 'connectorB'\n");
    corto_setOwner(connectorB);
    if (corto_update(b)) {
        goto error;
    }

    printf("Update object 'c' from the application\n");
    corto_setOwner(NULL);
    if (corto_update(c)) {
        goto error;
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
