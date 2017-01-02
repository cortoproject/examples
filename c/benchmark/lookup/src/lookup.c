#include "lookup.h"

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

void onUpdate(corto_object this, corto_eventMask mask, corto_object observable, corto_observer observer) {
}

typedef struct stats {
    corto_float64 min;
    corto_float64 avg;
    corto_float64 max;
} stats;

static stats benchmark(corto_uint32 n, corto_bool useResolve, corto_string lookup) {
    stats result = {0, 0, 0};

    int batch = n / 10;

    int iter;
    // Do n updates in 10 steps
    for (iter = 0; iter < 10; iter++) {
        benchmark_start();

        if (useResolve) {
            int i; for (i = 0; i < batch; i++) {
                corto_object o = corto_resolve(NULL, lookup);
                if (o) corto_release(o);
            }
        } else {
            int i; for (i = 0; i < batch; i++) {
                corto_object o = corto_lookup(NULL, lookup);
                if (o) corto_release(o);
            }
        }

        double t = benchmark_stop();
        if (!result.min || (t < result.min)) {
            result.min = t;
        }
        result.avg += t;
        if (t > result.max) {
            result.max = t;
        }
    }

    result.min /= batch;
    result.avg /= n;
    result.max /= batch;
    result.min *= (double)1000000000;
    result.avg *= (double)1000000000;
    result.max *= (double)1000000000;

    printf("%9.2f %9.2f %9.2f (%s)\n", result.min, result.avg, result.max, lookup);

    return result;
}

int lookupMain(int argc, char* argv[]) {
    printf("\n=== corto_lookup: (nanoseconds)\n");
    printf("%9s %9s %9s\n", "min", "avg", "max");
    benchmark(1000000, FALSE, "/");
    benchmark(1000000, FALSE, "/corto");
    benchmark(1000000, FALSE, "/corto/lang");
    benchmark(1000000, FALSE, "/corto/lang/class/construct");
    benchmark(1000000, FALSE, "/notexist");
    benchmark(1000000, FALSE, "/not/exist");
    benchmark(1000000, FALSE, "/does/not/exist");
    benchmark(1000000, FALSE, "/corto/not/exist");
    benchmark(1000000, FALSE, "/corto/lang/doesnotexist");

    printf("\n=== corto_resolve: (nanoseconds)\n");
    printf("%9s %9s %9s\n", "min", "avg", "max");
    benchmark(1000000, TRUE, "/");
    benchmark(1000000, TRUE, "/corto");
    benchmark(1000000, TRUE, "/corto/lang");
    benchmark(1000000, TRUE, "/corto/lang/class/construct");
    benchmark(1000000, TRUE, "/notexist");
    benchmark(1000000, TRUE, "/not/exist");
    benchmark(1000000, TRUE, "/does/not/exist");
    benchmark(1000000, TRUE, "/corto/not/exist");
    benchmark(1000000, TRUE, "/corto/lang/doesnotexist");
    printf("\n");

    return 0;
}
