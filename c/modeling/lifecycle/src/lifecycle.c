#include "include/lifecycle.h"

void cb(corto_observerEvent *e) {
    char *str = corto_ptr_str(&e->event, corto_eventMask_o, 0);
    corto_info("event: << %s >>", str);
    free(str);
}

int lifecycleMain(int argc, char *argv[]) {

    /* Create observer for data */
    corto_object data = corto_lookupAssert(root_o, "data", corto_void_o);
    corto_observer observer = corto_observe(CORTO_ON_SCOPE, data).callback(cb);

    /* Forward declare MyInstance */
    corto_info("function: 'declareChild'");
    Foo instance = FooDeclareChild(root_o, "data/MyInstance");

    /* Claim object to demonstrate transition to final state after all claims
     * are released */
    corto_info("function: 'claim'");
    corto_claim(instance);

    /* Set initial value */
    instance->value = 10;

    /* Define instance */
    corto_info("function: 'define'");
    if (corto_define(instance)) {
        goto error;
    }

    /* Begin update */
    corto_info("function: 'updateBegin'");    
    if (!corto_update_begin(instance)) {
        instance->value = 20;
    
        corto_info("function: 'updateEnd'");
        if (corto_update_end(instance)) {
            goto error;
        }
    } else {
        goto error;
    }

    /* Delete object */
    corto_info("function: 'delete'");
    if (corto_delete(instance)) {
        goto error;
    }

    /* Release object */
    corto_info("function: 'release'");    
    corto_release(instance);

    /* Delete observer */
    corto_delete(observer);

    return 0;
error:
    corto_error("%s", corto_lasterr());
    return -1;
}
