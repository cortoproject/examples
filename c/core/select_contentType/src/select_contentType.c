/* $CORTO_GENERATED
 *
 * select_contentType.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/select_contentType.h>

/* $header() */
/* select_contentType
 *
 * This example shows how to browse through objects using corto_select, and
 * the value from the object in a specified contentType (JSON in this case).
 *
 * The example also shows how to create a struct from scratch with the core API.
 * There are easier ways to achieve this with definition files and the c-binding.
 * See the c-binding examples for more details.
 */
/* $end */

int select_contentTypeMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a Point type, so we have something to serialize to JSON. This is
     * the same code as in the dynamic_struct example. */
    corto_struct Point = corto_declareChild(root_o, "Point", corto_struct_o);
        if (!Point) goto error;

        /* Create x member */
        corto_member x = corto_declareChild(Point, "x", corto_member_o);
            if (!x) goto error;
            corto_ptr_setref(&x->type, corto_int32_o);
            if (corto_define(x)) goto error;

        /* Create y member */
        corto_member y = corto_declareChild(Point, "y", corto_member_o);
            if (!y) goto error;
            corto_ptr_setref(&y->type, corto_int32_o);
            if (corto_define(y)) goto error;

        /* Finalize struct */
        if (corto_define(Point)) goto error;

    /* Create two instances of Point. */
    corto_object p1 = corto_declareChild(root_o, "p1", Point);
    if (!p1) {
        goto error;
    }

    *(corto_int32*)CORTO_OFFSET(p1, x->offset) = 10;
    *(corto_int32*)CORTO_OFFSET(p1, y->offset) = 10;
    if (corto_define(p1)) {
        goto error;
    }

    corto_object p2 = corto_declareChild(root_o, "p2", Point);
    if (!p2) {
        goto error;
    }

    *(corto_int32*)CORTO_OFFSET(p2, x->offset) = 20;
    *(corto_int32*)CORTO_OFFSET(p2, y->offset) = 30;
    if (corto_define(p2)) {
        goto error;
    }

    /* Select all instances of type Point, get value in JSON */
    corto_iter it;
    corto_int16 ret = corto_select("/", "*")
      .contentType("text/json")
      .type("/Point")
      .iter(&it);
    if (ret) {
        goto error;
    }

    while (corto_iter_hasNext(&it)) {
        corto_result *r = corto_iter_next(&it);
        corto_info("id = '%s', value = %s", r->id, corto_result_getText(r));
    }

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
