
#include <include/value_casting.h>

/* value_casting
 *
 * This example shows how to use the corto_value API to cast a value to a
 * different type.
 */

void printValue(char *expr, corto_value *v) {
    corto_type type = corto_value_typeof(v);
    corto_string str = corto_value_str(v, 0);
    corto_info("%s: %s (%s)", expr, str, corto_fullpath(NULL, type));
    corto_dealloc(str);
}

int value_castingMain(int argc, char *argv[]) {
    corto_value value, result = corto_value_empty();

    /* Cast integer to string */
    value = corto_value_int(10);
    if (corto_value_cast(&value, corto_string_o, &result)) {
        goto error;
    }

    /* Show result */
    printValue("string(10)", &result);
    corto_value_free(&result);

    /* Cast integer to boolean */
    value = corto_value_int(1);
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
}
