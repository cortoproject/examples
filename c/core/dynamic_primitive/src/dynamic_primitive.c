/* $CORTO_GENERATED
 *
 * dynamic_primitive.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/dynamic_primitive.h>

/* $header() */
/* dynamic_primitive
 *
 * This example shows how to dynamically create a new primitive type.
 */
/* $end */

int dynamic_primitiveMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a new integer type */
    corto_int long_o = corto_declareChild(root_o, "long", corto_int_o);
        if (!long_o) goto error;

        /* Set width member of the baseclass of 'int' (primitive) */
        corto_primitive(long_o)->width = CORTO_WIDTH_32;
        if (corto_define(long_o)) goto error;

    /* Create a new unsigned integer type */
    corto_int ulong_o = corto_declareChild(root_o, "ulong", corto_uint_o);
        if (!ulong_o) goto error;

        /* Set width member of the baseclass of 'int' (primitive) */
        corto_primitive(ulong_o)->width = CORTO_WIDTH_64;
        if (corto_define(ulong_o)) goto error;

    int32_t i = -10;
    char *long_str = corto_ptr_contentof(&i, long_o, "text/corto");
    char *ulong_str = corto_ptr_contentof(&i, ulong_o, "text/corto");

    corto_info("long = %s, ulong = %s", long_str, ulong_str);
    
    corto_dealloc(long_str);
    corto_dealloc(ulong_str);

    return 0;
error:
    return -1;
/* $end */
}
