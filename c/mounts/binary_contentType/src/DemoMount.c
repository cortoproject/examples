/* This is a managed file. Do not delete this comment. */

#include <include/binary_contentType.h>

int16_t binary_contentType_DemoMount_construct(
    binary_contentType_DemoMount this)
{
    if (corto_mount_setContentType(this, "binary/corto")) {
        goto error;
    }

    Point *foo_value = corto_mem_new(Point_o);
    foo_value->x = 10;
    foo_value->y = 20;

    /* Populate the mount with some demo data */
    corto_resultAssign(
        corto_resultListAppendAlloc(this->data),
        "foo",                      /* id */
        NULL,                       /* name */
        ".",                        /* parent */
        "binary_contentType/Point", /* type */
        (corto_word)foo_value,      /* value */
        CORTO_RESULT_LEAF           /* does object have children */
    );

    Point *bar_value = corto_mem_new(Point_o);
    bar_value->x = 30;
    bar_value->y = 40;

    corto_resultAssign(
        corto_resultListAppendAlloc(this->data),
        "bar",                      /* id */
        NULL,                       /* name */
        ".",                        /* parent */
        "binary_contentType/Point", /* type */
        (corto_word)bar_value,      /* value */
        CORTO_RESULT_LEAF           /* does object have children */
    );

    return corto_super_construct(this);
error:
    return -1;
}

corto_resultIter binary_contentType_DemoMount_onQuery(
    binary_contentType_DemoMount this,
    corto_query *query)
{
    return corto_ll_iterAlloc(this->data);
}

