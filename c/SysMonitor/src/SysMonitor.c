#include "SysMonitor.h"

int SysMonitorMain(int argc, char *argv[]) {

    /* Create DDP server on port 8000 */
    server_DDPCreateChild(NULL, "ddp", 8000);

    /* Create Stats collection */
    corto_object Stats_o = corto_voidCreateChild(NULL, "Stats");

    /* Create one system monitor for the current system */
    sys_Monitor mon_o = sys_MonitorCreateChild(Stats_o, "mon");

    /* Resolve static cpu information once */
    sys_Monitor_refresh(mon_o, Sys_CpuInfo);

    /* Infinite update loop */
    while (1) {
        /* The refresh method obtains new data and updates the object */
        sys_Monitor_refresh(mon_o, Sys_Cpu | Sys_Mem);

        /* Refresh every second */
        corto_sleep(1, 0);
    }

    return 0;
}
