/* _load.c
 *
 * This file is generated. Do not modify.
 */

#include <dependency_resolver.h>

int dependency_resolverMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    corto_start();
    if (dependency_resolverMain(argc, argv)) return -1;
    corto_stop();
    return 0;
}

