/* $CORTO_GENERATED
 *
 * DemoMount.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/sinksource.h>

corto_void _sinksource_DemoMount_add(
    sinksource_DemoMount this,
    corto_string id)
{
/* $begin(sinksource/DemoMount/add) */

    corto_resultAssign(
        corto_resultListAppendAlloc(this->objects), /* append new element */
        id,                     /* id */
        NULL,                   /* name (same as id) */
        ".",                    /* parent */
        "/sinksource/DemoType", /* type */
        (corto_word)"{5}",      /* default value */
        TRUE                    /* is node leaf (yes) */
    );

/* $end */
}

corto_int16 _sinksource_DemoMount_construct(
    sinksource_DemoMount this)
{
/* $begin(sinksource/DemoMount/construct) */
    corto_mount_setContentType(this, "text/corto");
    return corto_mount_construct(this);

/* $end */
}

corto_void _sinksource_DemoMount_onNotify(
    sinksource_DemoMount this,
    corto_eventMask event,
    corto_result *object)
{
/* $begin(sinksource/DemoMount/onNotify) */
    corto_value v = corto_value_value(corto_eventMask_o, &event);
    corto_info("%s: onNotify('%s', '%s')",
        corto_mount(this)->kind == CORTO_SINK ? "SINK" : "SOURCE", 
        corto_value_contentof(&v, "text/corto") + 3,
        object->id);

/* $end */
}

corto_resultIter _sinksource_DemoMount_onRequest(
    sinksource_DemoMount this,
    corto_request *request)
{
/* $begin(sinksource/DemoMount/onRequest) */

    corto_info("%s: onRequest('%s')",
        corto_mount(this)->kind == CORTO_SINK ? "SINK" : "SOURCE", request->expr);

    /* Create iterator for object list that outlives function scope */
    return corto_llIterAlloc(this->objects);
/* $end */
}

corto_int16 _sinksource_DemoMount_update(
    sinksource_DemoMount this,
    corto_string id,
    corto_int32 value)
{
/* $begin(sinksource/DemoMount/update) */
    corto_bool newObject = FALSE;

    corto_info("%s: corto_int32Update('%s', %d)",
        corto_mount(this)->kind == CORTO_SINK ? "SINK" : "SOURCE", id, value);

    /* Set owner for current thread to mount */
    corto_object prevOwner = corto_setOwner(this);

    /* Find or create object */
    sinksource_DemoType o = corto_findOrDeclare(corto_mount(this)->mount, id, sinksource_DemoType_o);
    if (!o) corto_error("%s", corto_lasterr());
    if (!corto_checkState(o, CORTO_DEFINED)) newObject = TRUE;
    
    /* Update object, set target or actual depending on ownership */
    corto_int32 result = corto_int32Update(o, value);

    /* Restore owner */
    corto_setOwner(prevOwner);

    /* Release object if it already existed */
    if (!newObject) corto_release(o);

    return result;
error:
    return -1;
/* $end */
}
