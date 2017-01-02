#include "admin.h"

int adminMain(int argc, char *argv[]) {

    /* Create admin server on port 8000 */
    admin_serverCreate(8000);

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
    corto_setstr(helloWorld, "Hello World!");

    /* Keep alive */
    while (1) {
        corto_sleep(1, 0);
    }

    /* Open the admin page on http://localhost:8000/admin/ */

    return 0;
}