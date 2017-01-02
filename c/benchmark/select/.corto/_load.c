/* _load.c
 *
 * This file is generated. Do not modify.
 */

#include <select.h>

int selectMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    corto_start();
    if (selectMain(argc, argv)) return -1;
    corto_stop();
    return 0;
}

