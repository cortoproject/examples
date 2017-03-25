/* $CORTO_GENERATED
 *
 * path_identifiers.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/path_identifiers.h>

/* $header() */
/* path_identifiers
 *
 * This example shows how to obtain path identifiers from objects.
 */
/* $end */

int path_identifiersMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a few (nested) objects */
    corto_object tier1 = corto_createChild(root_o, "tier1", corto_void_o);
    if (!tier1) {
        goto error;
    }

    corto_object tier2 = corto_createChild(tier1, "tier2", corto_void_o);
    if (!tier2) {
        goto error;
    }

    corto_object tier3 = corto_createChild(tier2, "tier3", corto_void_o);
    if (!tier3) {
        goto error;
    }

    /* Use the corto_idof function if you simply want to obtain the id of an
     * object without its parents. */
    printf("corto_idof(tier1): '%s'\n", corto_idof(tier1));

    /* The corto_fullpath function returns the shortest identifier that will
     * resolve an object from root, when using corto_resolve. */
    printf("corto_fullpath(NULL, tier1): '%s'\n", corto_fullpath(NULL, tier1));
    printf("corto_fullpath(NULL, tier2): '%s'\n", corto_fullpath(NULL, tier2));

    /* Because corto_resolve always looks first in corto/lang, corto_fullpath
     * can return just an id without parents for objects from that scope. */
    printf("corto_fullpath(NULL, corto_int32_o): '%s'\n", corto_fullpath(NULL, corto_int32_o));

    /* You can provide a buffer to the first argument of corto_fullpath. If you
     * leave it to NULL, corto will return a managed string which can be freed
     * by subsequent API calls. Up to CORTO_MAX_TLS_STRINGS (5) strings can be
     * used simultaneously. */
    corto_id id;
    printf("corto_fullpath(id, tier1): '%s'\n", corto_fullpath(id, tier1));
    printf("  id after corto_fullpath: '%s'\n", id);

    /* The corto_path function returns the shortest identifier that will resolve
     * an object from the 'from' parameter, when using corto_resolve. corto_path
     * also allows you to specify a custom separator. */
    printf("corto_path(NULL, tier1, tier3, \"/\"): '%s'\n", corto_path(NULL, tier1, tier3, "/"));

    /* When generating an id from NULL, corto_path will generate an initial / */
    printf("corto_path(NULL, NULL, tier1, \"/\"): '%s'\n", corto_path(NULL, NULL, tier1, "/"));
    printf("corto_path(NULL, root_o, tier1, \"/\"): '%s'\n", corto_path(NULL, root_o, tier1, "/"));

    /* The first argument of corto_path works the same as corto_fullpath */
    printf("corto_path(id, tier1, tier3, \"/\"): '%s'\n", corto_path(id, tier1, tier3, "/"));
    printf("  id after corto_path: '%s'\n", id);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
