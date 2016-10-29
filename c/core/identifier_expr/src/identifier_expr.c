#include "identifier_expr.h"

/* identifier_expr
 *
 * This example shows how to use the corto_match API. This API is used to match
 * a set of ids with an expression, and is used for example in corto_select,
 * corto_subscribe and the security framework.
 *
 * This example also shows how to compile and run expressions. This allows for
 * faster execution of expressions and is useful in particular when an expressions
 * has to be evaluated many times.
 *
 * The expression format is an extension of POSIX fnmatch (* and ? wildcards)
 * and additionally is capable of matching paths recursively (//), excluding ids
 * from the matched set (^) AND and OR operations (&, |) and the ability to
 * specify multiple expressions in one string (,).
 */

int identifier_exprMain(int argc, char *argv[]) {

    /* Simple expression */
    printf("match(fo?, foo) = %d\n", corto_match("fo?", "foo"));

    /* NOT expression */
    printf("match(^foo, foo) = %d\n", corto_match("^foo", "foo"));

    /* OR expression */
    printf("match(foo|bar, bar) = %d\n", corto_match("foo|bar", "bar"));

    /* AND expression */
    printf("match(*fo*&*ba*, foobar) = %d\n", corto_match("*fo*&*ba*", "foobar"));

    /* Scope expression */
    printf("match(foo/*, foo/bar) = %d\n", corto_match("foo/*", "foo/bar"));

    /* Returns FALSE, as the number of elements must match exactly */
    printf("match(foo/*, foo/bar/hello) = %d\n", corto_match("foo/*", "foo/bar/hello"));

    /* Recursive scope expression */
    printf("match(foo//*, foo/bar/hello/world) = %d\n", corto_match("foo//*", "foo/bar/hello/world"));

    /* Use multiple expressions in single string */
    printf("match(foo,//bar, hello/bar) = %d\n", corto_match("foo,//bar", "hello/bar"));
    printf("match(foo,//bar, foo) = %d\n", corto_match("foo,//bar", "foo"));

    /* Show how to use a compiled expression */
    corto_matchProgram program = corto_matchProgram_compile("//^foo|bar", TRUE, TRUE);

    /* Compare performance of a program vs. just corto_match */
    corto_time start, stop;
    corto_timeGet(&start);

    /* Measure corto_match */
    int i;
    for (i = 0; i < 100000; i++) {
        corto_match("//^foo|bar", "/hello/world/zoo"); // matching value
        corto_match("//^foo|bar", "/hello/world/bar"); // non-matching value
    }
    corto_timeGet(&stop);
    stop = corto_timeSub(stop, start);
    printf("corto_match took %.2f ms (1 million iterations)\n", corto_timeToDouble(stop) * 1000);

    /* Measure compiled program */
    corto_timeGet(&start);
    for (i = 0; i < 100000; i++) {
        corto_matchProgram_run(program, "/hello/world/zoo"); // matching value
        corto_matchProgram_run(program, "/hello/world/bar"); // non-matching value
    }
    corto_timeGet(&stop);
    stop = corto_timeSub(stop, start);
    printf("matchProgram_run took %.2f ms (1 million iterations)\n", corto_timeToDouble(stop) * 1000);

    /* Cleanup resources */
    corto_matchProgram_free(program);

    return 0;
}
