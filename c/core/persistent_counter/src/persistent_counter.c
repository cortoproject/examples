#include <include/persistent_counter.h>

int persistent_counterMain(int argc, char *argv[]) {
    /* Load configuration */
    corto_load("config.json", 0, NULL);

    /* Create a new object, or resume it from persistent store */
    int32_t *i = corto_createChild(root_o, "data/i", corto_int32_o);

    /* Update object with a new value */
    corto_update_begin(i);
    (*i) ++;
    corto_update_end(i);

    /* Print new value to console */
    printf("i = %d\n", *i);

    return 0;
}
