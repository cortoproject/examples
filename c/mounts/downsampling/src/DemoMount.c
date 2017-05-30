/* $CORTO_GENERATED
 *
 * DemoMount.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/downsampling.h>

void _downsampling_DemoMount_onNotify(
    downsampling_DemoMount this,
    corto_subscriberEvent *event)
{
/* $begin(downsampling/DemoMount/onNotify) */

    char *str = corto_ptr_str(&event->event, corto_eventMask_o, 0);
    corto_info(
        "'%s' received for '%s' from '%s' with type '%s' and value %s",
        str + 3 /* Strip ON_ */,
        event->data.id,
        event->data.parent,
        event->data.type,
        corto_result_getText(&event->data));
    corto_dealloc(str);

/* $end */
}
