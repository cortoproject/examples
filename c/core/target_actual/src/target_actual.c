
#include <include/target_actual.h>

/* target_actual
 *
 * This example shows how to use the corto/lang/target type for implementing
 * remote control scenario's. Target types contain a "target" and "actual" field
 * that represent the actual and desired state of a value.
 *
 * Target types provide a mechanism consistent with corto ownership to request
 * changes to values that are not owned by an application.
 */

/* C representation of the target type */
typedef struct temperatureControl {
    corto_int32 actual;
    corto_int32 target;
    corto_int32 objective;
} temperatureControl;

int target_actualMain(int argc, char *argv[]) {

    /* Create an int32 target type that represents a temperature */
    corto_target temperatureControl_o = corto_declare(corto_target_o);
    if (!temperatureControl_o) {
        goto error;
    }
    corto_ptr_setref(&temperatureControl_o->type, corto_int32_o);
    if (corto_define(temperatureControl_o)) {
        goto error;
    }

    /* Create a new mount that will own an instance of temperatureControl */
    corto_mount m = corto_create(corto_mount_o);
    if (!m) {
        goto error;
    }

    /* Set the current owner to be the mount */
    corto_object prev = corto_setOwner(m);

    /* Create a temperatureControl instance that is owned by the mount */
    temperatureControl *dial = corto_create(temperatureControl_o);

    /* Reset the current owner back to the application (NULL) */
    corto_setOwner(prev);

    /* Update temperature with new target. Had the object not been of a target
     * type this would not have been possible because the object is owned by
     * the mount, not the application. */
    if (!corto_update_begin(dial)) {
        /* A well behaving app should only set target */
        dial->target = 60;
        if (corto_update_end(dial)) {
            goto error;
        }
    } else {
        goto error;
    }

    /* The previous code explicitly sets the target member. When using generated
     * code from the C binding, the Create, Set, Assign and Update functions
     * automatically set either target or actual depending on the owner. */

    /* Another (safe) way of assigning target members is by deserializing a value
     * into the object. The deserializer will set either target or actual depending
     * on the context, but never both. */
    if (!corto_update_begin(dial)) {

        /* This code only sets 'target' and discards 'actual' */
        corto_fromcontent(dial, "text/corto", "{target=10, actual=20}");
        if (corto_update_end(dial)) {
           goto error;
        }
    } else {
        goto error;
    }

    /* If the mount is set as owner, the 'actual' member will be set */
    prev = corto_setOwner(m);
    if (!corto_update_begin(dial)) {

        /* This code only sets 'actual' and discards 'target' */
        corto_fromcontent(dial, "text/corto", "{target=30, actual=40}");
        if (corto_update_end(dial)) {
           goto error;
        }
    } else {
        goto error;
    }
    corto_setOwner(prev);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
