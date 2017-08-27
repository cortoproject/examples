/* This is a managed file. Do not delete this comment. */

#include <include/nested.h>


/* This example shows how to use a nested struct with an enumeration */

int nestedMain(int argc, char *argv[]) {

    /* Create two Point values on the stack */
    nested_Point
        start = {10, 20},
        stop = {30, 40};

    /* Create new instance of the Line type. Pass pointers to the nested struct
     * to the Create function. These will be copied into the new object. */
    nested_Line *l = nested_LineCreate(Nested_Blue, &start, &stop);
    if (!l) {
        goto error;
    }

    /* Use dynamic string conversion */
    char *str = corto_contentof(l, "text/json");
    corto_info("l = %s", str);
    corto_dealloc(str);

    /* Send update notification for new value */
    nested_LineUpdate(l, Nested_Green, &start, &stop);

    /* Notice that generated enumeration constants automatically adjust their
     * caps to the constant identifier. If the constants would've been defined
     * with all caps, the constant would've been NESTED_GREEN. Similarly, if the
     * constant would've been defined lowercase, it would've been nested_green.
     *
     * An enumeration shall always use only one convention which is typically
     * derived from the first constant. 
     */

    /* Access members natively */
    corto_info("l->color = '%s', l->start = {%d, %d), l->stop = {%d, %d}", 
        /* Trick to get enum constant id without allocating string */
        corto_idof(corto_enum_constant(nested_color_o, l->color)),
        l->start.x, l->start.y, 
        l->stop.x, l->stop.y);

    corto_delete(l);

    return 0;
error:
    corto_error("%s", corto_lasterr());
    return -1;
}

