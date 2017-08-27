/* $CORTO_GENERATED
 *
 * event.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/event.h>

/* $header() */
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

static stats benchmark(int observers, int n, corto_bool publish, corto_eventMask scope, corto_bool voidType) {
    // Array to hold observers
    corto_observer *observerArray = malloc(observers * sizeof(corto_object));
    corto_object observable, parent, child, grandChild;
    corto_string observableId;
    corto_string value;
    stats result = {0, 0, 0};

    // Observable
    if (voidType) {
        parent = corto_voidCreateChild(root_o, "parent");
        child = corto_voidCreateChild(parent, "child");
        grandChild = corto_voidCreateChild(child, "grandChild");
    } else {
        parent = corto_int32CreateChild(root_o, "parent", 0);
        child = corto_int32CreateChild(parent, "child", 0);
        grandChild = corto_int32CreateChild(child, "grandChild", 0);
        value = "10";
    }

    // Create observers
    int i;
    for (i = 0; i < observers; i ++) {
        if (scope == CORTO_ON_SELF) {
            observerArray[i] = corto_observe(CORTO_UPDATE, parent).callback(onUpdate);
        } else if (scope == CORTO_ON_SCOPE) {
            observerArray[i] = corto_observe(CORTO_UPDATE|CORTO_ON_SCOPE, parent).callback(onUpdate);
        } else if (scope == CORTO_ON_TREE) {
           observerArray[i] = corto_observe(CORTO_UPDATE|CORTO_ON_TREE, parent).callback(onUpdate);
       }
    }

    if (scope == CORTO_ON_SELF) {
        observable = parent;
        observableId = "/parent";
    } else if (scope == CORTO_ON_SCOPE) {
        observable = child;
        observableId = "/parent/child";
    } else if (scope == CORTO_ON_TREE) {
        observable = grandChild;
        observableId = "/parent/child/grandChild";
    }

    int batch = n / 10;

    int iter;
    // Do n updates in 10 steps
    for (iter = 0; iter < 10; iter++) {
        benchmark_start();

        if (!publish) {
            if (voidType) {
                for (i = 0; i < batch; i ++) {
                    corto_update(observable);
                }
            } else {
                for (i = 0; i < batch; i ++) {
                    corto_updateBegin(observable);
                    corto_updateEnd(observable);
                }
            }
        } else {
            for (i = 0; i < batch; i ++) {
                corto_publish(CORTO_UPDATE, observableId, "void", "text/corto", value);
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

    // Cleanup
    for (i = 0; i < observers; i ++) {
        corto_delete(observerArray[i]);
    }

    corto_dealloc(observerArray);
    corto_delete(parent);

    result.min /= batch;
    result.avg /= n;
    result.max /= batch;
    result.min *= (double)1000000000;
    result.avg *= (double)1000000000;
    result.max *= (double)1000000000;

    return result;
}

void benchmark_set(corto_bool publish, corto_eventMask scope, corto_bool voidType) {
    printf("%5s %8s ",
        voidType ? "void" : "int32",
        scope == CORTO_ON_SELF ? "ON_SELF" : scope == CORTO_ON_SCOPE ? "ON_SCOPE" : "ON_TREE");

    stats b_0 = benchmark(0, 1000000, publish, scope, voidType);
    stats b_1 = benchmark(1, 1000000, publish, scope, voidType);
    stats b_5 = benchmark(5, 1000000, publish, scope, voidType);
    stats b_50 = benchmark(50, 100000, publish, scope, voidType);
    stats b_500 =   benchmark(500, 100000, publish, scope, voidType);
    printf("%9.1f %9.1f %9.1f %9.1f %9.1f %9.1f %9.1f %9.1f %10.1f %10.1f",
      b_0.avg, b_0.min,
      b_1.avg, b_1.min,
      b_5.avg, b_5.min,
      b_50.avg, b_50.min,
      b_500.avg, b_500.min);

    printf("\n");
}
/* $end */

int eventMain(int argc, char *argv[]) {
/* $begin(main) */
    printf("\n=== corto_update:\n");
    printf("%5s %8s %s\n",
        "",  "", " observers (nanosec/event)");
    printf("%5s %8s %9s %9s %9s %9s %9s %9s %9s %9s %10s %10s\n",
        "type", "scope",
        "0 avg", "0 min", "1 avg", "1 min", "5 avg", "5 min", "50 avg", "50 min", "500 avg", "500 min");

    benchmark_set(FALSE, CORTO_ON_SELF, TRUE);
    benchmark_set(FALSE, CORTO_ON_SCOPE, TRUE);
    benchmark_set(FALSE, CORTO_ON_TREE, TRUE);
    benchmark_set(FALSE, CORTO_ON_SELF, FALSE);
    benchmark_set(FALSE, CORTO_ON_SCOPE, FALSE);
    benchmark_set(FALSE, CORTO_ON_TREE, FALSE);

    printf("\n=== corto_publish:\n");
    printf("%5s %8s %s\n",
        "",  "", " observers (nanosec/event)");
    printf("%5s %8s %9s %9s %9s %9s %9s %9s %9s %9s %10s %10s\n",
        "type", "scope",
        "0 avg", "0 min", "1 avg", "1 min", "5 avg", "5 min", "50 avg", "50 min", "500 avg", "500 min");
    benchmark_set(TRUE, CORTO_ON_SELF, TRUE);
    benchmark_set(TRUE, CORTO_ON_SCOPE, TRUE);
    benchmark_set(TRUE, CORTO_ON_TREE, TRUE);
    benchmark_set(TRUE, CORTO_ON_SELF, FALSE);
    benchmark_set(TRUE, CORTO_ON_SCOPE, FALSE);
    benchmark_set(TRUE, CORTO_ON_TREE, FALSE);

    printf("\n");

    return 0;
/* $end */
}
