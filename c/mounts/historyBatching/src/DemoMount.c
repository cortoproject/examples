/* This is a managed file. Do not delete this comment. */

#include <include/historyBatching.h>

void historyBatching_DemoMount_onHistoryBatchNotify(
    historyBatching_DemoMount this,
    anonymous_historyBatching_0 events)
{
    int count = 0;
    corto_time _t;
    corto_timeGet(&_t);
    double t = corto_timeToDouble(_t);
    
    corto_info("%s: >> batch start (%f)", corto_idof(this), t);
    while (corto_iter_hasNext(&events)) {
        corto_subscriberEvent *event = corto_iter_next(&events);
        char *str = corto_ptr_str(&event->event, corto_eventMask_o, 0);
        /*corto_info(
            "'%s' received for '%s' from '%s' with type '%s' and value %s",
            str,
            event->data.id,
            event->data.parent,
            event->data.type,
            corto_result_getText(&event->data));*/
        corto_dealloc(str);
        count ++;
    }
    corto_info("%s: << batch end (%d samples)", corto_idof(this), count);
    printf("\n");
}

