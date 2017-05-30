/* $CORTO_GENERATED
 *
 * write.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/write.h>

/* $header() */
/* $end */

int writeMain(int argc, char *argv[]) {
/* $begin(main) */
    /* Load configuration */
    corto_load("config.json", 0, NULL);

    /* Publish create of a virtual object (triggers DEFINE on mount) */
    corto_publish(CORTO_ON_DEFINE, "data/foo", "int32", "text/json", "10");

    /* Create the 'data' scope in the store */
    corto_object data = corto_createChild(root_o, "data", corto_void_o);
    
    /* Create an object in the data scope (triggers DEFINE on mount) */
    corto_int32 *bar = corto_createChild(data, "bar", corto_int32_o);

    /* Update object (triggers UPDATE on mount) */
    corto_int32Update(bar, 20);

    /* Note that 'bar' is created with an initialial value set to '0'. If you
     * want to set the initial value to a custom value, see the 
     * core/objects_fwddecl example on how to do that. */

    return 0;
/* $end */
}
