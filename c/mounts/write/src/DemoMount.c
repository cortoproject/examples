/* This is a managed file. Do not delete this comment. */

#include <include/write.h>

void write_DemoMount_onNotify(
    write_DemoMount this,
    corto_subscriberEvent *event)
{

    char *str = corto_ptr_str(&event->event, corto_eventMask_o, 0);
    corto_info(
        "'%s' received for '%s' from '%s' with type '%s' and value %s",
        str,
        event->data.id,
        event->data.parent,
        event->data.type,
        corto_result_getText(&event->data));
    corto_dealloc(str);

}

