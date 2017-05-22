/* $CORTO_GENERATED
 *
 * rest.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/rest.h>

/* $header() */
/* Enter code outside of main here. */
/* $end */

int restMain(int argc, char *argv[]) {
/* $begin(main) */
    /* Create a service on the same port that serves a REST API */
    rest_Server rest = rest_ServerCreate(8000, "api", "/");
    if (!rest) {
        goto error;
    }

    /* Create a service on port 8000 that serves up index.html */
    server_Files content = server_FilesCreate(8000, "", ".");
    if (!content) {
        goto error;
    }

    /* Create dummy data */
    corto_object example = corto_createChild(root_o, "example", corto_void_o);
    corto_int32 *foo = corto_createChild(example, "foo", corto_int32_o);
    corto_int32 *bar = corto_createChild(example, "bar", corto_int32_o);
    corto_string *helloWorld = corto_createChild(example, "helloWorld", corto_string_o);
    corto_float32 *foo_child = corto_createChild(foo, "child", corto_float32_o);
    corto_float32 *bar_child = corto_createChild(bar, "child", corto_float32_o);

    /* Set values */
    *foo = 10;
    *bar = 20;
    *foo_child = 10.5;
    *bar_child = 20.5;
    corto_ptr_setstr(helloWorld, "Hello World!");

    /* Keep server alive */
    while (1) {
        corto_sleep(1, 0);
    }

    return 0;
error:
    corto_error("rest: %s", corto_lasterr());
    return -1;
/* $end */
}
