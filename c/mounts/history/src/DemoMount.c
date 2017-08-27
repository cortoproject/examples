/* This is a managed file. Do not delete this comment. */

#include <include/history.h>

int16_t history_DemoMount_construct(
    history_DemoMount this)
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
        (corto_word)"Hello World",  /* value */
        CORTO_RESULT_LEAF           /* does object have children */
    );

    /* Create history samples to the two results */

    return corto_super_construct(this);
}

corto_resultIter history_DemoMount_onHistoryQuery(
    history_DemoMount this,
    corto_query *query)
{

    /* << Insert implementation >> */

}

