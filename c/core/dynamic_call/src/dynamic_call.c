/* $CORTO_GENERATED
 *
 * dynamic_call.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/dynamic_call.h>

/* $header() */
/* dynamic_call
 *
 * This example shows how to use corto_call to dynamically call corto functions.
 */
corto_int32 add(corto_int32 a, corto_int32 b) {
    return a + b;
}
/* $end */

int dynamic_callMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a function object in Corto, assign it with a C function */
    corto_function f = corto_declareChild(root_o, "add(int32 a,int32 b)", corto_function_o);
    f->kind = CORTO_PROCEDURE_CDECL;
    f->fptr = (corto_word)add;
    corto_setref(&f->returnType, corto_int32_o);
    if (corto_define(f)) {
        goto error;
    }

    /* Now call it */
    corto_int32 result;
    corto_call(f, &result, 10, 20);
    printf("corto_call, result = %d\n", result);

    /* Call it with an array of arguments */
    corto_int32 a = 20, b = 30;
    void *args[] = {&a, &b};
    corto_callb(f, &result, args);
    printf("corto_callb, result = %d\n", result);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
