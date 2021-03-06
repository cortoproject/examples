/* This is a managed file. Do not delete this comment. */

#include <include/read.h>

int16_t read_DemoMount_construct(
    read_DemoMount this)
{

    /* Populate the mount with some demo data */
    corto_resultAssign(
        corto_resultListAppendAlloc(this->data),
        "foo",                      /* id */
        NULL,                       /* name */
        ".",                        /* parent */
        "int32",                    /* type */
        (corto_word)"10",           /* value */
        CORTO_RESULT_LEAF           /* does object have children */
    );

    corto_resultAssign(
        corto_resultListAppendAlloc(this->data),
        "bar",                      /* id */
        NULL,                       /* name */
        ".",                        /* parent */
        "string",                   /* type */
        (corto_word)"\"Hello World\"",  /* value */
        CORTO_RESULT_LEAF           /* does object have children */
    );

    return corto_super_construct(this);
}

corto_resultIter read_DemoMount_onQuery(
    read_DemoMount this,
    corto_query *query)
{
    corto_iter it = corto_ll_iter(this->data);

    while (corto_iter_hasNext(&it)) {
        corto_result *r = corto_iter_next(&it);
        if (corto_query_match(query, r)) {
            corto_mount_return(this, r);
        }
    }

    return CORTO_ITER_EMPTY;
}

