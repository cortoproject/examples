/* $CORTO_GENERATED
 *
 * identifier_expr.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/identifier_expr.h>

/* $header() */
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
/* $end */

int identifier_exprMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Simple expression */
    corto_info("match('fo?', 'foo') = %d", corto_idmatch("fo?", "foo"));

    /* NOT expression */
    corto_info("match('^foo', 'foo') = %d", corto_idmatch("^foo", "foo"));

    /* OR expression */
    corto_info("match('foo|bar', 'bar') = %d", corto_idmatch("foo|bar", "bar"));

    /* AND expression */
    corto_info("match('*fo*&*ba*', 'foobar') = %d", corto_idmatch("*fo*&*ba*", "foobar"));

    /* Scope expression */
    corto_info("match('foo/*', 'foo/bar') = %d", corto_idmatch("foo/*", "foo/bar"));

    /* Returns FALSE, as the number of elements must match exactly */
    corto_info("match('foo/*', 'foo/bar/hello') = %d", corto_idmatch("foo/*", "foo/bar/hello"));

    /* Recursive scope expression */
    corto_info("match('foo//*', 'foo/bar/hello/world') = %d", corto_idmatch("foo//*", "foo/bar/hello/world"));

    /* Use multiple expressions in single string */
    corto_info("match('foo,//bar', 'hello/bar') = %d", corto_idmatch("foo,//bar", "hello/bar"));
    corto_info("match('foo,//bar', 'foo') = %d", corto_idmatch("foo,//bar", "foo"));

    /* Show how to use a compiled expression */
    corto_idmatch_program program = corto_idmatch_compile("//^foo|bar", TRUE, TRUE);

    /* Compare performance of a program vs. just corto_match */
    corto_time start, stop;
    corto_timeGet(&start);

    /* Measure corto_match */
    int i;
    for (i = 0; i < 100000; i++) {
        corto_idmatch("//^foo|bar", "/hello/world/zoo"); // matching value
        corto_idmatch("//^foo|bar", "/hello/world/bar"); // non-matching value
    }
    corto_timeGet(&stop);
    stop = corto_timeSub(stop, start);
    corto_info("corto_match took %.2f ms (1 million iterations)", corto_timeToDouble(stop) * 1000);

    /* Measure compiled program */
    corto_timeGet(&start);
    for (i = 0; i < 100000; i++) {
        corto_idmatch_run(program, "/hello/world/zoo"); // matching value
        corto_idmatch_run(program, "/hello/world/bar"); // non-matching value
    }
    corto_timeGet(&stop);
    stop = corto_timeSub(stop, start);
    corto_info("matchProgram_run took %.2f ms (1 million iterations)", corto_timeToDouble(stop) * 1000);

    /* Cleanup resources */
    corto_idmatch_free(program);

    return 0;
/* $end */
}
