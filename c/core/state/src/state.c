
#include <include/state.h>

/* state
 *
 * This example shows how an object state changes while it goes through
 * different lifecycle stages.
 */

void printState(corto_object o) {
    corto_state state = corto_stateof(o);
    char *state_str = corto_ptr_str(&state, corto_state_o, 0);
    corto_info("state of '%s' is '%s'", corto_idof(o), state_str);
    corto_dealloc(state_str);
}

int stateMain(int argc, char *argv[]) {

    /* Declare a signed integer object in the global object hierarchy */
    int32_t *i = corto_declareChild(root_o, "i", corto_int32_o);
    if (!i) {
        goto error;
    }

    printState(i);

    if (corto_define(i)) {
        goto error;
    }

    printState(i);

    /* Change the value of the object */
    if (!corto_updateBegin(i)) {
        *i = 10;
        if (corto_updateEnd(i)) {
            goto error;
        }
    } else {
        goto error;
    }

    /* State doesn't change after an update */
    printState(i);

    /* To demonstrate how a state changes after a delete, we will take a
     * claim on the object. Alive claims ensure an object won't be
     * deallocated until they are released. */
    corto_claim(i);

    /* Delete the object */
    if (corto_delete(i)) {
        goto error;
    }

    printState(i);

    /* This will deallocate the object */
    corto_release(i);

    return 0;
error:
    corto_error("%s", corto_lasterr());
    return -1;
}
