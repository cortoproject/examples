/* $CORTO_GENERATED
 *
 * value_casting.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/value_casting.h>

/* $header() */
/* value_casting
 *
 * This example shows how to use the corto_value API to cast a value to a
 * different type.
 */

void printValue(char *expr, corto_value *v) {
    corto_type type = corto_value_getType(v);
    corto_string str = corto_strv(v, 0);
    printf("%s: %s (%s)\n", expr, str, corto_fullpath(NULL, type));
    corto_dealloc(str);
}
/* $end */

int value_castingMain(int argc, char *argv[]) {
/* $begin(main) */
    corto_value value, result = corto_value_init();

    /* Cast integer to string */
    value = corto_value_literalInteger(10);
    if (corto_value_cast(&value, corto_string_o, &result)) {
        goto error;
    }

    /* Show result */
    printValue("string(10)", &result);
    corto_value_free(&result);

    /* Cast integer to boolean */
    value = corto_value_literalInteger(1);
    if (corto_value_cast(&value, corto_bool_o, &result)) {
        goto error;
    }

    /* Show result */
    printValue("bool(1)", &result);
    corto_value_free(&result);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
