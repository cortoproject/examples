/* $CORTO_GENERATED
 *
 * DemoMount.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/mount_write.h>

void _mount_write_DemoMount_onNotify(
    mount_write_DemoMount this,
    corto_subscriberEvent *event)
{
/* $begin(mount_write/DemoMount/onNotify) */

    corto_info(
        "event received for '%s' from '%s' with type '%s' and value %s",
        event->data.id,
        event->data.parent,
        event->data.type,
        corto_result_getText(&event->data));

/* $end */
}
