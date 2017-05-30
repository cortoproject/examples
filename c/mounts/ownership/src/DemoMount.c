/* $CORTO_GENERATED
 *
 * DemoMount.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/ownership.h>

void _ownership_DemoMount_add(
    ownership_DemoMount this,
    corto_string id)
{
/* $begin(ownership/DemoMount/add) */
    corto_resultAssign(
        corto_resultListAppendAlloc(this->objects), /* append new element */
        id,                     /* id */
        NULL,                   /* name (same as id) */
        ".",                    /* parent */
        "/ownership/DemoType", /* type */
        (corto_word)"{5}",      /* default value */
        TRUE                    /* is node leaf (yes) */
    );
/* $end */
}

int16_t _ownership_DemoMount_construct(
    ownership_DemoMount this)
{
/* $begin(ownership/DemoMount/construct) */
    corto_mount_setContentType(this, "text/corto");
    return corto_mount_construct(this);
/* $end */
}

void _ownership_DemoMount_onNotify(
    ownership_DemoMount this,
    corto_subscriberEvent *event)
{
/* $begin(ownership/DemoMount/onNotify) */
    char *str = corto_ptr_str(&event, corto_eventMask_o, 0);
    corto_info("%s: onNotify('%s', '%s')",
        corto_idof(this),
        str + 3,
        event->data.id);
    corto_dealloc(str);

/* $end */
}

corto_resultIter _ownership_DemoMount_onQuery(
    ownership_DemoMount this,
    corto_query *query)
{
/* $begin(ownership/DemoMount/onQuery) */
    corto_info("%s: onQuery(select='%s', from='%s')",
        corto_idof(this),
        query->select,
        query->from);

    /* Create iterator for object list that outlives function scope */
    return corto_ll_iterAlloc(this->objects);
/* $end */
}

int16_t _ownership_DemoMount_update(
    ownership_DemoMount this,
    corto_string id,
    int32_t value)
{
/* $begin(ownership/DemoMount/update) */
    corto_bool newObject = FALSE;

    corto_info("%s: corto_int32Update('%s', %d)",
        corto_idof(this),
        id,
        value);

    /* Set owner for current thread to mount */
    corto_object prevOwner = corto_setOwner(this);

    /* Find or create object */
    ownership_DemoType o = corto_findOrDeclare(corto_mount(this)->mount, id, ownership_DemoType_o);
    if (!o) corto_error("%s", corto_lasterr());
    if (!corto_checkState(o, CORTO_DEFINED)) newObject = TRUE;

    /* Update object, set target or actual depending on ownership */
    corto_int32 result = corto_int32Update(o, value);

    /* Restore owner */
    corto_setOwner(prevOwner);

    /* Release object if it already existed */
    if (!newObject) corto_release(o);

    return result;
/* $end */
}
