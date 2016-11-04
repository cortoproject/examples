#include "mount_fibo.h"

/* mount_fibo
 *
 * This example shows how to create a connector that mounts the fibonacci sequence.
 * It showcases how the corto mount interface can be utilized to use very little
 * resources while exposing (literally) unlimited datasets.
 */

struct iterData {
    uint64_t current;
    char id[21];
    char value[21];
    corto_result result;
};

/* Somewhat efficient iterative fibonacci implementation */
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

void* next(corto_iter *it) {
    struct iterData *data = it->udata;
    uint64_t value = fibo(data->current);
    sprintf(data->id, "%lu", data->current);
    sprintf(data->value, "%lu", value);
    data->result.id = data->id;
    data->result.value = (corto_word)data->value;
    data->current ++;
    return &data->result;
}

void release(corto_iter *it) {
    corto_dealloc(it->udata);
}

int isnumber(char *str) {
    char *ptr = str;
    for(ptr = str; isdigit(*ptr); ptr++);
    return *ptr == '\0';
}

/* This mount implements custom next and hasNext functions to ensure that only
 * the record that is iterated over is stored in memory. */
corto_iter onRequest(corto_object mount, corto_request *request) {
    corto_iter result;

    /* Create data for iterator, prepare static fields of result */
    struct iterData *data = corto_calloc(sizeof(struct iterData));
    if (isnumber(request->expr)) {
        data->current = atoi(request->expr);
    } else {
        data->current = request->offset;
    }
    data->result.parent = ".";
    data->result.type = "uint64";
    data->result.leaf = TRUE;
    result.udata = data;

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
    corto_setref(&corto_interface(FiboClass)->base, corto_mount_o);

    /* Create onNotify method (called when the mount receives an update) */
    corto_method onRequestMethod = corto_declareChild(
        FiboClass,
        "onRequest(core/request request)",
        corto_method_o);
    if (!onRequestMethod) {
        goto error;
    }

    corto_function(onRequestMethod)->kind = CORTO_PROCEDURE_CDECL;
    corto_function(onRequestMethod)->fptr = (corto_word)onRequest;

    if (corto_define(onRequestMethod)) {
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

    /* Encode data in the corto string format */
    corto_setstr(&corto_subscriber(connector)->contentType, "text/corto");
    if (corto_define(connector)) {
        goto error;
    }

    return connector;
error:
    return NULL;
}

int mount_fiboMain(int argc, char *argv[]) {
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
    corto_resultIter it;
    corto_select("/fibo", "*").limit(0, 10).contentType("text/corto").iter(&it);
    {corto_resultIterForeach(it, result) {
        printf("fibo(%s) = %s\n", result.id, corto_result_getText(&result));
    }}
    printf("\n");

    /* Request fibonacci numbers 50 to 60 */
    corto_select("/fibo", "*").limit(50, 10).contentType("text/corto").iter(&it);
    {corto_resultIterForeach(it, result) {
        printf("fibo(%s) = %s\n", result.id, corto_result_getText(&result));
    }}
    printf("\n");

    /* Request fibonacci number 75 */
    corto_select("/fibo", "75").contentType("text/corto").iter(&it);
    {corto_resultIterForeach(it, result) {
        printf("fibo(%s) = %s\n", result.id, corto_result_getText(&result));
    }}

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
