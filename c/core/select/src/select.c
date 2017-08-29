
#include <include/select.h>

/* $header() */
/* select
 *
 * This example shows a simple example of how to use the corto_select API to
 * browse objects.
 */

void iterate(corto_iter *it) {
    while(corto_iter_hasNext(it)) {
        corto_result *r = corto_iter_next(it);
        corto_info("id: '%s', parent: '%s', type: '%s'", 
            r->id, r->parent, r->type);
    }
}

int selectMain(int argc, char *argv[]) {
    corto_iter it;
    corto_int16 ret;

    /* Create a dummy (nested) objects */
    corto_object tier1 = corto_createChild(root_o, "tier1", corto_void_o);
    if (!tier1) {
        goto error;
    }

    corto_object tier2A = corto_createChild(tier1, "tier2A", corto_void_o);
    if (!tier2A) {
        goto error;
    }

    corto_object tier2B = corto_createChild(tier1, "tier2B", corto_void_o);
    if (!tier2B) {
        goto error;
    }

    corto_object tier3 = corto_createChild(tier2A, "tier3", corto_void_o);
    if (!tier3) {
        goto error;
    }


    /* Select all objects in the tier1 scope. The first argument to corto_select
     * specifies te offset from which the 'parent' member in the result will be
     * computed. */
    ret = corto_select("*").from("/tier1").iter(&it);
    if (ret) {
        goto error;
    }

    corto_info("corto_select(\"*\").from(\"/tier1\")");
    iterate(&it);


    /* This example returns the same objects, but the parent is relative to the
     * root. Note that the 'parent' in the result is equivalent to the result of
     * using corto_path with as offset the first argument of corto_select. */
    ret = corto_select("tier1/*").iter(&it);
    if (ret) {
        goto error;
    }

    printf("\n");
    corto_info("corto_select(\"tier/*\")");
    iterate(&it);


    /* This example recursively returns all objects from tier1, depth first. */
    ret = corto_select("//").from("/tier1").iter(&it);
    if (ret) {
        goto error;
    }

    printf("\n");
    corto_info("corto_select(\"//\").from(\"/tier\")");
    iterate(&it);

    /* This example recursively returns objects from tier1 that except objects
     * of which their id ends with 2A */
    ret = corto_select("//^*2A").from("/tier1").iter(&it);
    if (ret) {
        goto error;
    }

    printf("\n");
    corto_info("corto_select(\"//^*2A\").from(\"/tier1\")");
    iterate(&it);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
