/* This is a managed file. Do not delete this comment. */

#include <include/ownership.h>


void notify(corto_subscriberEvent *e) {
    char *str = corto_ptr_str(&e->event, corto_eventMask_o, 0);
    corto_info("main: onNotify('%s', '%s'): %s",
        str + 3 /* strip 'ON_' */,
        e->data.id,
        corto_result_getText(&e->data));
    corto_dealloc(str);
}

int ownershipMain(int argc, char *argv[]) {

    /* This example shows mounts with local and remote ownership.
     *
     * Objects loaded from a mount with LOCAL_OWNER ownership will be owned
     * locally by the application. Objects loaded from a mount with REMOTE_OWNER
     * ownership will be owned by the mount representing the remote datasource.
     *
     * LOCAL_OWNER mounts can only change objects owned by the application.
     * 
     * REMOTE_OWNER mounts can only change objects that are not owned by the application.
     *
     * If an application creates an object that is managed by a LOCAL_OWNER mount,
     * the latest value will be restored automatically from the mount.
     *
     * This application uses a 'target' type (DemoType), which contains a 'target'
     * and an 'actual' field. If the object owner updates the object, the 'actual'
     * field will be set, otherwise the 'target' will be set.
     */

    /* Load mount configuration */
    if (corto_load("config.json", 0, NULL)) {
        goto error;
    }

    /* Create a subscriber */
    corto_subscriber sub = corto_subscribe("/data/*")
        .contentType("text/json")
        .callback(notify);

    /* Create and populate sink mount */
    ownership_DemoMount local = corto_lookupAssert(root_o, "local", ownership_DemoMount_o);
    ownership_DemoMount_add(local, "foo");

    /* Create and populate source mount */
    ownership_DemoMount remote = corto_lookupAssert(root_o, "remote", ownership_DemoMount_o);
    ownership_DemoMount_add(remote, "bar");

    /* Create the local 'foo' object. It will be resumed from the local mount. Note
     * that the value of 'foo' will be set to '5' by the mount. */
    printf("\n");
    corto_info("main: corto_createChild('data', 'foo', 'ownership/DemoType')");
    corto_object data = corto_createChild(root_o, "data", corto_void_o);
    ownership_DemoType foo = corto_createChild(data, "foo", ownership_DemoType_o);

    /* Update foo from main (sets actual) */
    printf("\n");
    corto_info("main: corto_int32Update('foo', 10)");
    corto_int32Update(foo, 10);

    /* Update foo from local mount (sets actual) */
    printf("\n");
    ownership_DemoMount_updateObject(local, "foo", 20);

    /* Update foo from remote mount (sets target) */
    printf("\n");
    ownership_DemoMount_updateObject(remote, "foo", 30);

    /* Update bar from remote (sets actual) */
    printf("\n");
    ownership_DemoMount_updateObject(remote, "bar", 10);

    /* Update bar from local (sets target) */
    printf("\n");
    ownership_DemoMount_updateObject(local, "bar", 20);

    /* Update bar from main (sets target) */
    printf("\n");
    corto_info("main: corto_int32Update('bar', 30)");
    ownership_DemoType bar = corto_lookupAssert(data, "bar", ownership_DemoType_o);
    corto_int32Update(bar, 30);

    /* Cleanup subscriber */
    corto_delete(sub);

    return 0;
error:
    corto_error("%s", corto_lasterr());
    return -1;
}

