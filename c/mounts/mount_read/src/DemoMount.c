/* $CORTO_GENERATED
 *
 * DemoMount.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/mount_read.h>

int16_t _mount_read_DemoMount_construct(
    mount_read_DemoMount this)
{
/* $begin(mount_read/DemoMount/construct) */

    /* Populate the mount with some demo data */
    corto_resultAssign(
        corto_resultListAppendAlloc(this->data),
        "foo",                      /* id */
        NULL,                       /* name */
        ".",                        /* parent */
        "int32",                    /* type */
        (corto_word)"10",           /* value */
        TRUE                        /* is node a leaf */
    );

    corto_resultAssign(
        corto_resultListAppendAlloc(this->data),
        "bar",                      /* id */
        NULL,                       /* name */
        ".",                        /* parent */
        "string",                   /* type */
        (corto_word)"Hello World",  /* value */
        TRUE                        /* is node a leaf */
    );

    return corto_super_construct(this);
/* $end */
}

corto_resultIter _mount_read_DemoMount_onQuery(
    mount_read_DemoMount this,
    corto_query *query)
{
/* $begin(mount_read/DemoMount/onQuery) */

    /* Return iterator to the data that outlives this function scope */
    return corto_ll_iterAlloc(this->data);
/* $end */
}
