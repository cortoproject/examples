/* $CORTO_GENERATED
 *
 * Replicator_CarBrands.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include "Replicator.h"

corto_int16 _Replicator_CarBrands_construct(Replicator_CarBrands this) {
/* $begin(Replicator/CarBrands/construct) */

    /* Create list with some dummy items. These represent objects from a
     * remote source. In a typical scenario, this data could be gathered from
     * other datasources like a database or REST interface. */
    *(corto_resultListAppendAlloc(this->items)) = (corto_result) {
        corto_strdup("Audi"),   /* Name */
        corto_strdup("."),      /* Parent relative to query */
        corto_strdup("Brand")   /* Type */
    };

    *(corto_resultListAppendAlloc(this->items)) = (corto_result) {
        corto_strdup("BMW"),    /* Name */
        corto_strdup("."),      /* Parent relative to query */
        corto_strdup("Brand")   /* Type */
    };

    *(corto_resultListAppendAlloc(this->items)) = (corto_result) {
        corto_strdup("Ford"),   /* Name */
        corto_strdup("."),      /* Parent relative to query */
        corto_strdup("Brand")   /* Type */
    };

    *(corto_resultListAppendAlloc(this->items)) = (corto_result) {
        corto_strdup("Toyota"), /* Name */
        corto_strdup("."),      /* Parent relative to query */
        corto_strdup("Brand")   /* Type */
    };

    *(corto_resultListAppendAlloc(this->items)) = (corto_result) {
        corto_strdup("Volkswagen"), /* Name */
        corto_strdup("."),          /* Parent relative to query */
        corto_strdup("Brand")       /* Type */
    };

    /* Call base constructor */
    return corto_replicator_construct(this);
/* $end */
}

corto_resultIter _Replicator_CarBrands_onRequest(Replicator_CarBrands this, corto_object parent, corto_string expr) {
/* $begin(Replicator/CarBrands/onRequest) */

    return corto_llIterAlloc(this->items);

/* $end */
}
