/* _load.c
 *
 * This file is generated. Do not modify.
 */

#include <lookup.h>

int lookupMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    corto_start();
    if (lookupMain(argc, argv)) return -1;
    corto_stop();
    return 0;
}

