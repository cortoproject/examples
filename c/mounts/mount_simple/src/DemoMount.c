/* $CORTO_GENERATED
 *
 * DemoMount.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/mount_simple.h>

int16_t _mount_simple_DemoMount_construct(
    mount_simple_DemoMount this)
{
/* $begin(mount_simple/DemoMount/construct) */

    /* SOURCE means data served up by the mount is not owned by the app. */
    corto_mount(this)->kind = CORTO_SOURCE;

    /* Data served up by the mount is in the corto string format */
    corto_mount_setContentType(this, "text/corto");

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

corto_resultIter _mount_simple_DemoMount_onRequest(
    mount_simple_DemoMount this,
    corto_request *request)
{
/* $begin(mount_simple/DemoMount/onRequest) */

    /* Return iterator to the data that outlives this function scope */
    return corto_ll_iterAlloc(this->data);
/* $end */
}
