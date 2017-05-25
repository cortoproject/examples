/* $CORTO_GENERATED
 *
 * sys_rest.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/sys_rest.h>

/* $header() */
/* Enter code outside of main here. */
/* $end */

int sys_restMain(int argc, char *argv[]) {
/* $begin(main) */

    sys_Monitor mon = sys_MonitorCreateChild(root_o, "mon");

    server_RESTCreate(8000, "api", "");
    server_FilesCreate(8000, "", ".");

    while (1) {
        sys_Monitor_refresh(mon, Sys_Cpu | Sys_Mem);
        corto_sleep(1, 0);
    }

    return 0;
/* $end */
}
