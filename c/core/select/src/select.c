/* $CORTO_GENERATED
 *
 * select.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/select.h>

/* $header() */
/* select
 *
 * This example shows a simple example of how to use the corto_select API to
 * browse objects.
 */

void iterate(corto_iter *it) {
    while(corto_iterHasNext(it)) {
        corto_result *r = corto_iterNext(it);
        printf("id: '%s', parent: '%s', type: '%s'\n", r->id, r->parent, r->type);
    }
}
/* $end */

int selectMain(int argc, char *argv[]) {
/* $begin(main) */
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
    ret = corto_select("/tier1", "*").iter(&it);
    if (ret) {
        goto error;
    }

    printf("corto_select(\"/tier1\", \"*\"):\n");
    iterate(&it);


    /* This example returns the same objects, but the parent is relative to the
     * root. Note that the 'parent' in the result is equivalent to the result of
     * using corto_path with as offset the first argument of corto_select. */
    ret = corto_select("/", "tier1/*").iter(&it);
    if (ret) {
        goto error;
    }

    printf("\n");
    printf("corto_select(\"/\", \"tier/*\"):\n");
    iterate(&it);


    /* This example recursively returns all objects from tier1, depth first. */
    ret = corto_select("/tier1", "//").iter(&it);
    if (ret) {
        goto error;
    }

    printf("\n");
    printf("corto_select(\"/tier\", \"//\"):\n");
    iterate(&it);

    /* This example recursively returns objects from tier1 that except objects
     * of which their id ends with 2A */
    ret = corto_select("/tier1", "//^*2A").iter(&it);
    if (ret) {
        goto error;
    }

    printf("\n");
    printf("corto_select(\"/tier1\", \"//^*2A\"):\n");
    iterate(&it);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
