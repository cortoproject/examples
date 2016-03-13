/* _load.c
 *
 * This file is generated. Do not modify.
 */

#include "corto/corto.h"
#include "Rest.h"

int main(int argc, char* argv[]) {
corto_start();
    if (corto_load("/corto/web", 0, NULL)) return -1;
    if (corto_load("/corto/web/server", 0, NULL)) return -1;
    int RestMain(int argc, char* argv[]);
    if (RestMain(argc, argv)) return -1;
    corto_stop();
    return 0;
}

