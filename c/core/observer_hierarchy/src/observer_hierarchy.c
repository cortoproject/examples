/* $CORTO_GENERATED
 *
 * observer_hierarchy.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/observer_hierarchy.h>

/* $header() */
/* observer_hierarchy
 *
 * This example shows how to create observers that listen for notifications on a
 * tree of objects.
 */

void onNotifyScope(corto_observerEvent *e)
{
    corto_info("onNotifyScope: trigger for '%s'", corto_fullpath(NULL, e->data));
}

void onNotifyTree(corto_observerEvent *e)
{
    corto_info("onNotifyTree: trigger for '%s'", corto_fullpath(NULL, e->data));
}
/* $end */

int observer_hierarchyMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Observe notifications for children of root */
    corto_observer onScope = corto_observe(CORTO_ON_DEFINE|CORTO_ON_SCOPE, root_o)
      .callback(onNotifyScope);

    /* Observe notifications for tree of root */
    corto_observer onTree = corto_observe(CORTO_ON_DEFINE|CORTO_ON_TREE, root_o)
      .callback(onNotifyTree);

    /* This object will trigger the onScope and onTree */
    corto_object tier1 = corto_createChild(root_o, "tier1", corto_void_o);
    if (!tier1) {
        goto error;
    }

    /* This object will only trigger onTree */
    corto_object tier2 = corto_createChild(tier1, "tier2", corto_void_o);
    if (!tier2) {
        goto error;
    }

    /* Delete observers */
    if (corto_delete(onScope)) {
        goto error;
    }

    if (corto_delete(onTree)) {
        goto error;
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
