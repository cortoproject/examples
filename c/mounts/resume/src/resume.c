#include <include/resume.h>

void printObject(corto_object o) {
    char *value = corto_contentof(o, "text/json");
    corto_info("object '%s'", corto_fullpath(NULL, o));
    corto_info("  type: '%s'", corto_fullpath(NULL, corto_typeof(o)));
    corto_info("  value: '%s'", value);
    free(value);
}

int resumeMain(int argc, char *argv[]) {

    /* Load mount configuration, data is mounted under /data */
    if (corto_load("config.json", 0, NULL)) {
        goto error;
    }

    /* Create object data/foo (value will be set by mount/onResume) */
    corto_object foo = corto_createChild(NULL, "data/foo", corto_int32_o);
    if (!foo) {
        goto error;
    }

    /* Print details of 'foo' */
    printObject(foo);

    /* Lookup object data/bar (object will be created by mount/onResume) */
    corto_object bar = corto_lookup(NULL, "data/bar");
    if (!bar) {
        goto error;
    }

    /* Print details of 'bar' */
    printObject(bar);

    return 0;
error:
    corto_error("%s", corto_lasterr());
    return -1;
}
