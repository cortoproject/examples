/* _project.c
 *
 * This file is generated. Do not modify.
 */

#include <eventCrash.h>

int eventCrashMain(int argc, char* argv[]);

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char* argv[]) {
    corto_start();
    if (eventCrashMain(argc, argv)) return -1;
    corto_stop();
    return 0;
}

