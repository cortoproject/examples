/* This is a managed file. Do not delete this comment. */

#include <include/downsampling.h>

void downsampling_DemoMount_onNotify(
    downsampling_DemoMount this,
    corto_subscriberEvent *event)
{

    char *str = corto_ptr_str(&event->event, corto_eventMask_o, 0);
    corto_info(
        "'%s' received for '%s' from '%s' with type '%s' and value %s",
        str + 3 /* Strip ON_ */,
        event->data.id,
        event->data.parent,
        event->data.type,
        corto_result_getText(&event->data));
    corto_dealloc(str);

}

