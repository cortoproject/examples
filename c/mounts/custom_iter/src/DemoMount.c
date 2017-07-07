/* This is a managed file. Do not delete this comment. */

#include <include/custom_iter.h>



/* Iterator context */
struct iter_data {
    corto_result result; /* Result that will be returned by iterator */
    char id[2];          /* Id of the result */
    char value[12];      /* Value of the result */
};

/* As long as hasNext returns true, 'next' will be called */
int hasNext(corto_iter *it) {
    struct iter_data *data = it->ctx;
    return data->id[0] != 'z'; /* Iterate until we had the entire alphabet */
}

/* Progress iterator, return value */
void* next(corto_iter *it) {
    struct iter_data *data = it->ctx;

    if (!data->id[0]) {
        data->id[0] = 'a'; /* Start with 'a' */
    } else {
        data->id[0] ++; /* Increase letter */
    }

    /* Memory of value will be freed by whomever is calling the mount */
    data->result.value = (intptr_t)strdup(data->value);

    return &data->result;
}

/* Release iterator resources */
void release(corto_iter *it) {
    struct iter_data *data = it->ctx;
    free(data);
}

corto_resultIter custom_iter_DemoMount_onQuery(
    custom_iter_DemoMount this,
    corto_query *query)
{
    corto_iter result;

    /* Prepare iterator context */
    struct iter_data *data = malloc(sizeof(struct iter_data));
    strcpy(data->id, "");
    strcpy(data->value, "Hello World");

    /* Set members of result that don't change while iterating */
    data->result.id = data->id;
    data->result.parent = ".";
    data->result.type = "string";
    data->result.leaf = true;

    /* Prepare iterator with custom next, hasNext and release functions */
    result.ctx = data;
    result.hasNext = hasNext;
    result.next = next;
    result.release = release;

    /* Return custom iterator */
    return result;
}

