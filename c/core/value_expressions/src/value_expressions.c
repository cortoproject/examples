#include "value_expressions.h"

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
    corto_type type = corto_value_getType(v);
    corto_string str = corto_strv(v, 0);
    printf("%20s: %s (%s)\n", expr, str, corto_fullpath(NULL, type));
    corto_dealloc(str);
}

int value_expressionsMain(int argc, char *argv[]) {
    corto_value left, right, result = corto_value_init();

    /* Add two integers */
    left = corto_value_literalInteger(10);
    right = corto_value_literalInteger(20);
    if (corto_value_binaryOperator(CORTO_ADD, &left, &right, &result)) {
        goto error;
    }

    /* Show result */
    printValue("10 + 20", &result);
    corto_value_free(&result);


    /* Subtract two numbers of different type */
    left = corto_value_literalFloatingPoint(20.5);
    right = corto_value_literalInteger(10);
    if (corto_value_binaryOperator(CORTO_SUB, &left, &right, &result)) {
        goto error;
    }

    /* Show result */
    printValue("20.5 - 10", &result);
    corto_value_free(&result);


    /* Add a number to a string */
    left = corto_value_literalInteger(10);
    right = corto_value_literalString(" + 20 = 30");
    if (corto_value_binaryOperator(CORTO_ADD, &left, &right, &result)) {
        goto error;
    }

    /* Show result */
    printValue("10 + \" + 20 = 30\"", &result);
    corto_value_free(&result);


    /* Evaluate a conditional expression */
    left = corto_value_literalString("Foo");
    right = corto_value_literalString("Bar");
    if (corto_value_binaryOperator(CORTO_COND_EQ, &left, &right, &result)) {
        goto error;
    }

    /* Show result */
    printValue("\"Foo\" == \"Bar\"", &result);
    corto_value_free(&result);


    return 0;
error:
    return -1;
}
