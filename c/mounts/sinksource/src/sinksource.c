/* $CORTO_GENERATED
 *
 * sinksource.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/sinksource.h>

/* $header() */
void notify(corto_object instance, corto_eventMask event, corto_result *object, corto_subscriber sub) {
    corto_value v = corto_value_value(corto_eventMask_o, &event);
    corto_info("main: onNotify('%s', '%s'): %s",
        corto_value_contentof(&v, "text/corto") + 3,
        object->id,
        corto_result_getText(object));
}
/* $end */

int sinksourceMain(int argc, char *argv[]) {
/* $begin(main) */

    /* This example demonstrates the difference between SINK and SOURCE mounts.
     * A SOURCE mount represents a remote data source. A SINK mount represents a
     * local (typically persistent) data source.
     *
     * SINK mounts only can only change objects owned by the application.
     * 
     * SOURCE mounts can only change objects that are not owned by the application.
     *
     * If an application creates an object that is managed by a SINK mount,
     * corto will automatically restore the latest value from the SINK.
     *
     * This application uses a 'target' type (DemoType), which contains a 'target'
     * and an 'actual' field. If the object owner updates the object, the 'actual'
     * field will be set, otherwise the 'target' will be set.
     */

    /* Create a mount point to which we will connect a SINK and a SOURCE */
    corto_object data = corto_createChild(root_o, "data", corto_void_o);

    /* Create a subscriber */
    corto_subscriber sub = corto_subscribe(CORTO_ON_ANY, "/data", "*")
        .contentType("text/json")
        .callback(notify);

    /* Create and populate sink mount */
    sinksource_DemoMount snk = sinksource_DemoMountCreate(CORTO_SINK, data);
    sinksource_DemoMount_add(snk, "foo");

    /* Create and populate source mount */
    sinksource_DemoMount src = sinksource_DemoMountCreate(CORTO_SOURCE, data);
    sinksource_DemoMount_add(src, "bar");

    /* Create the local 'foo' object. It will be resumed from the SINK. Note
     * that the value of 'foo' will be set to '5' by the mount. */
    printf("\n");
    corto_info("main: corto_createChild('data', 'foo', 'sinksource/DemoType')");
    sinksource_DemoType foo = corto_createChild(data, "foo", sinksource_DemoType_o);

    /* Update foo from main */
    printf("\n");
    corto_info("main: corto_int32Update('foo', 10)");
    corto_int32Update(foo, 10);

    /* Update foo from sink mount */
    printf("\n");
    sinksource_DemoMount_update(snk, "foo", 20);

    /* Update foo from source mount */
    printf("\n");
    sinksource_DemoMount_update(src, "foo", 30);

    /* Update bar from source */
    printf("\n");
    sinksource_DemoMount_update(src, "bar", 10);

    /* Update bar from sink */
    printf("\n");
    sinksource_DemoMount_update(snk, "bar", 20);

    /* Update bar from main */
    printf("\n");
    corto_info("main: corto_int32Update('bar', 30)");
    sinksource_DemoType bar = corto_lookup(data, "bar");
    corto_int32Update(bar, 30);
    corto_release(bar);

    return 0;
/* $end */
}
