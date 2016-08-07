/* $CORTO_GENERATED
 *
 * PerfTest.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <PerfTest/PerfTest.h>

/* $header() */
static corto_time start;

void benchmark_start() {
    corto_timeGet(&start);
}
double benchmark_stop() {
    corto_time stop;
    corto_timeGet(&stop);
    start = corto_timeSub(stop, start);
    return corto_timeToDouble(start);
}

void onUpdate(corto_object me, corto_object observable) {
}

static void benchmark_update(int observers, int n) {
    // Array to hold observers
    corto_observer *observerArray = malloc(observers * sizeof(corto_object));

    // Observable
    corto_voidCreateChild_auto(root_o, obj);

    // Create observers
    int i;
    for (i = 0; i < observers; i ++) {
        observerArray[i] = corto_observerCreate(CORTO_ON_UPDATE, obj, onUpdate);
    }

    // Do n updates
    benchmark_start();
    for (i = 0; i < n; i ++) {
        corto_update(obj);
    }
    double t = benchmark_stop();
    printf("benchmark_update (%d observers): %.f events/sec (%.2f nanosec/event)\n",
      observers,
      (double)n / t,
      (t / n) * (double)1000000000);

    // Cleanup
    for (i = 0; i < observers; i ++) {
        corto_delete(observerArray[i]);
    }
    corto_dealloc(observerArray);
    corto_delete(obj);
}

static void benchmark_updateMount(int observers, int n) {
    // Array to hold observers
    PerfTest_MyMount *mountArray = malloc(observers * sizeof(corto_object));

    // Observable
    corto_voidCreateChild_auto(root_o, parent);
    corto_voidCreateChild_auto(parent, obj);

    // Create observers
    int i;
    for (i = 0; i < observers; i ++) {
        if (!(mountArray[i] = PerfTest_MyMountCreate(parent))) {
            corto_error("%s", corto_lasterr());
        }
    }

    // Do n updates
    benchmark_start();
    for (i = 0; i < n; i ++) {
        corto_update(obj);
    }
    double t = benchmark_stop();
    printf("benchmark_updateMount (%d observers): %.f events/sec (%.2f nanosec/event)\n",
      observers,
      (double)n / t,
      (t / n) * (double)1000000000);

    // Cleanup
    for (i = 0; i < observers; i ++) {
        if (mountArray[i]) {
            corto_delete(mountArray[i]);
        }
    }
    corto_dealloc(mountArray);
    corto_delete(obj);
    corto_delete(parent);
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
/* $end */

int PerfTestMain(int argc, char* argv[]) {
/* $begin(main) */

    // Benchmark create + delete
    benchmark_createDelete(10000000);
    benchmark_createDeleteChild(10000000);

    printf("\n");

    // Benchmark updates with varying numbers of observers */
    benchmark_update(0, 10000000);
    benchmark_update(1, 10000000);
    benchmark_update(5, 10000000);
    benchmark_update(10, 10000000);
    benchmark_update(50, 10000000);
    benchmark_update(100, 10000000);

    printf("\n");

    // Benchmark updates with varying numbers of mounts (max = 16) */
    benchmark_updateMount(0, 10000000);
    benchmark_updateMount(1, 10000000);
    benchmark_updateMount(5, 10000000);
    benchmark_updateMount(10, 10000000);

    return 0;
/* $end */
}
