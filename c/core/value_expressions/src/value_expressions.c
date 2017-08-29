
#include <include/value_expressions.h>

/* value_expressions
 *
 * This example shows how to use the corto_value API to evaluate expressions on
 * any kind of corto value.
 *
 * The corto_value type is primarily used in serializers. It contains not just
 * a type and a pointer to a value, but also metadata about the kind of value,
 * for example, whether it is an object, member or element.
 *
 * The corto_value functions can be found in the corto_value.h header.
 */

void printValue(char *expr, corto_value *v) {
    corto_type type = corto_value_typeof(v);
    corto_string str = corto_value_str(v, 0);
    corto_info("%20s: %s ('%s')", expr, str, corto_fullpath(NULL, type));
    corto_dealloc(str);
}

int value_expressionsMain(int argc, char *argv[]) {
    corto_value left, right, result = corto_value_empty();

    /* Add two integers */
    left = corto_value_int(10);
    right = corto_value_int(20);
    if (corto_value_binaryOp(CORTO_ADD, &left, &right, &result)) {
        goto error;
    }

    /* Show result */
    printValue("10 + 20", &result);
    corto_value_free(&result);


    /* Subtract two numbers of different type */
    left = corto_value_float(20.5);
    right = corto_value_int(10);
    if (corto_value_binaryOp(CORTO_SUB, &left, &right, &result)) {
        goto error;
    }

    /* Show result */
    printValue("20.5 - 10", &result);
    corto_value_free(&result);


    /* Add a number to a string */
    left = corto_value_int(10);
    right = corto_value_string(" + 20 = 30");
    if (corto_value_binaryOp(CORTO_ADD, &left, &right, &result)) {
        goto error;
    }

    /* Show result */
    printValue("10 + \" + 20 = 30\"", &result);
    corto_value_free(&result);


    /* Evaluate a conditional expression */
    left = corto_value_string("Foo");
    right = corto_value_string("Bar");
    if (corto_value_binaryOp(CORTO_COND_EQ, &left, &right, &result)) {
        goto error;
    }

    /* Show result */
    printValue("\"Foo\" == \"Bar\"", &result);
    corto_value_free(&result);


    return 0;
error:
    return -1;
}
