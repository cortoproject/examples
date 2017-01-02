#include "create_delete.h"

static corto_time start;

void benchmark_start(void) {
    corto_timeGet(&start);
}
double benchmark_stop(void) {
    corto_time stop;
    corto_timeGet(&stop);
    start = corto_timeSub(stop, start);
    return corto_timeToDouble(start);
}

static void benchmark_createDeleteChild(corto_uint32 n) {

    benchmark_start();
    corto_int32 i;
    for (i = 0; i < n; i ++) {
        corto_voidCreateChild_auto(root_o, obj);
        corto_delete(obj);
    }
    double t = benchmark_stop();
    printf("benchmark_createDeleteChild: %.f cycles/sec (%.2f nanosec/cycle)\n",
      (double)n / t,
      (t / n) * (double)1000000000);
}


static void benchmark_createDelete(corto_uint32 n) {

    benchmark_start();
    corto_int32 i;
    for (i = 0; i < n; i ++) {
        corto_voidCreate_auto(obj);
        corto_delete(obj);
    }
    double t = benchmark_stop();
    printf("benchmark_createDelete: %.f cycles/sec (%.2f nanosec/cycle)\n",
      (double)n / t,
      (t / n) * (double)1000000000);
}

int create_deleteMain(int argc, char *argv[]) {

    benchmark_createDelete(1000000);
    benchmark_createDeleteChild(1000000);

    return 0;
}
