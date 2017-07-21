/* $CORTO_GENERATED
 *
 * mount_fibo.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/mount_fibo.h>

/* $header() */
/* mount_fibo
 *
 * This example shows how to create a connector that mounts the fibonacci sequence.
 * It demonstrates how a corto mount can be built to use very little
 * resources while exposing a (literally) unlimited dataset.
 *
 * This example uses advanced techniques to dynamically a new class, add a method
 * to that class and implement a custom iterator. It is recommended to study
 * some of the more basic examples first, like 'dynamic_struct' and 'objects'.
 */

/* iterative fibonacci implementation */
uint64_t fibo(uint64_t n) {
    if (n == 0) return 0;
    uint64_t previous = 0;
    uint64_t current = 1;
    uint64_t i;
    for (i = 1; i < n; ++i) {
        uint64_t next = previous + current;
        previous = current;
        current = next;
    }
    return current;
}

int hasNext(corto_iter *it) {
    return 1; /* there is always more data */
}

/* Context data for iterator */
struct iterData {
    uint64_t current; /* Current fibonacci number */
    char id[21]; /* Buffer to hold id (stringified current) */
    corto_result result; /* Result that the iterator will return */
};

void* next(corto_iter *it) {
    struct iterData *ctx = it->ctx;
    char valueBuffer[21]; /* Buffer to hold result (stringified fibo(current)) */

    /* Compute fibonacci number */
    uint64_t value = fibo(ctx->current);

    /* Set the id of the object and value in the result */
    sprintf(ctx->id, "%lu", ctx->current);
    sprintf(valueBuffer, "%lu", value);
    ctx->result.value = (corto_word)corto_strdup(valueBuffer);

    /* Increase fibonacci number */
    ctx->current ++;

    return &ctx->result;
}

void release(corto_iter *it) {
    corto_dealloc(it->ctx);
}

int isnumber(char *str) {
    char *ptr = str;
    for(ptr = str; isdigit(*ptr); ptr++);
    return *ptr == '\0';
}

/* This mount implements custom next and hasNext functions to ensure that only
 * the record that is iterated over is stored in memory. */
corto_iter onQuery(corto_object mount, corto_query *query) {
    corto_iter result;

    /* Create context data for the iterator */
    struct iterData *ctx = corto_calloc(sizeof(struct iterData));

    /* Support queries for a single number or starting from an offset */
    if (isnumber(query->select)) ctx->current = atoi(query->select);
    else ctx->current = query->offset;

    /* Preset id and value to reusable buffers in the iterData structure */
    ctx->result.id = ctx->id;

    /* Set values that will be the same for every result */
    ctx->result.parent = ".";
    ctx->result.type = "uint64";
    ctx->result.flags = CORTO_RESULT_LEAF;
    result.ctx = ctx;

    /* Set iterator callbacks */
    result.hasNext = hasNext;
    result.next = next;
    result.release = release;

    return result;
}

/* Create a class that mounts fibonacci numbers in corto */
corto_class createFiboClass(void) {
    corto_class FiboClass = corto_declareChild(root_o, "FiboConnector", corto_class_o);
    if (!FiboClass) {
        goto error;
    }

    /* Inherit from the corto mount class */
    corto_ptr_setref(&corto_interface(FiboClass)->base, corto_mount_o);

    /* Create onQuery method (called when API requests data, typically a corto_select) */
    corto_method onQueryMethod = corto_declareChild(
        FiboClass,
        "onQuery(core/query query)",
        corto_override_o);
    if (!onQueryMethod) {
        goto error;
    }

    corto_function(onQueryMethod)->kind = CORTO_PROCEDURE_CDECL;
    corto_function(onQueryMethod)->fptr = (corto_word)onQuery;

    if (corto_define(onQueryMethod)) {
        goto error;
    }

    /* Finalize class */
    if (corto_define(FiboClass)) {
        goto error;
    }

    return FiboClass;
error:
    return NULL;
}

/* Create instance of Fibo class */
corto_mount createMountInstance(corto_class mountClass) {
    corto_mount connector = corto_declareChild(root_o, "fibo", mountClass);
    if (!connector) {
        goto error;
    }

    /* Return data in the corto string format */
    corto_mount_setContentType(connector, "text/corto");

    if (corto_define(connector)) {
        goto error;
    }

    return connector;
error:
    return NULL;
}
/* $end */

int mount_fiboMain(int argc, char *argv[]) {
/* $begin(main) */
    /* Create class that mounts fibonacci numbers */
    corto_class FiboClass = createFiboClass();
    if (!FiboClass) {
        goto error;
    }

    /* Create instance of fibonacci mount */
    corto_mount connector = createMountInstance(FiboClass);
    if (!connector) {
        goto error;
    }

    /* Request fibonacci numbers 0 to 10 */
    corto_iter it;
    corto_select("fibo/*").limit(0, 10).contentType("text/corto").iter(&it);
    while (corto_iter_hasNext(&it)) {
        corto_result *r = corto_iter_next(&it);
        corto_info("fibo(%s) = %s", r->id, corto_result_getText(r));

    }
    printf("\n");

    /* Request fibonacci numbers 50 to 60 */
    corto_select("fibo/*").limit(50, 10).contentType("text/corto").iter(&it);
    while (corto_iter_hasNext(&it)) {
        corto_result *r = corto_iter_next(&it);
        corto_info("fibo(%s) = %s", r->id, corto_result_getText(r));
    }
    printf("\n");

    /* Request fibonacci number 75 */
    corto_select("fibo/75").contentType("text/corto").iter(&it);
    while (corto_iter_hasNext(&it)) {
        corto_result *r = corto_iter_next(&it);
        corto_info("fibo(%s) = %s", r->id, corto_result_getText(r));

    }
    printf("\n");



    corto_select("RED").from("dds/Circle").require("durability.kind", "PERSISTENT");
    corto_select("GREEN").from("dds/Circle").require("durability.kind", "PERSISTENT");



    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
