#include <include/dynamic_call.h>

/** dynamic_call
 *
 * This example shows how to use corto_call to dynamically call corto functions.
 */
int32_t add(int32_t a, int32_t b) {
    return a + b;
}

int dynamic_callMain(int argc, char *argv[]) {

    /* Create a function object in Corto, assign it with a C function */
    corto_function f = corto_declareChild(root_o, "add(int32 a,int32 b)", corto_function_o);
    f->kind = CORTO_PROCEDURE_CDECL;
    f->fptr = (corto_word)add;
    corto_ptr_setref(&f->returnType, corto_int32_o);
    if (corto_define(f)) {
        goto error;
    }

    /* Now call it */
    int32_t result;
    corto_call(f, &result, 10, 20);
    corto_info("corto_call, result = %d", result);

    /* Call it with an array of arguments */
    int32_t a = 20, b = 30;
    void *args[] = {&a, &b};
    corto_callb(f, &result, args);
    corto_info("corto_callb, result = %d", result);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
