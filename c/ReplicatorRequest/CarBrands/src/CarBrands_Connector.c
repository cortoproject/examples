/* $CORTO_GENERATED
 *
 * CarBrands_Connector.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include "CarBrands.h"

corto_int16 _CarBrands_Connector_construct(CarBrands_Connector this) {
/* $begin(CarBrands/Connector/construct) */

    /* Create list with some dummy items. These represent objects from a
     * remote source. In a typical scenario, this data could be gathered from
     * other datasources like a database or REST interface. */
    corto_resultSet(
        corto_resultListAppendAlloc(this->items),
        "Audi",   /* Name */
        ".",      /* Parent relative to query */
        "/CarBrands/Brand",   /* Type */
        0
    );

    corto_resultSet(
        corto_resultListAppendAlloc(this->items),
        "BMW",    /* Name */
        ".",      /* Parent relative to query */
        "/CarBrands/Brand",   /* Type */
        0
    );

    corto_resultSet(
        corto_resultListAppendAlloc(this->items),
        "Ford",   /* Name */
        ".",      /* Parent relative to query */
        "/CarBrands/Brand",   /* Type */
        0
    );

    corto_resultSet(
        corto_resultListAppendAlloc(this->items),
        "Toyota", /* Name */
        ".",      /* Parent relative to query */
        "/CarBrands/Brand",   /* Type */
        0
    );

    corto_resultSet(
        corto_resultListAppendAlloc(this->items),
        "Volkswagen", /* Name */
        ".",          /* Parent relative to query */
        "/CarBrands/Brand",       /* Type */
        0
    );

    /* Call base constructor. This will activate the replicator, and register
     * with the scope provided in the 'mount' member. */
    return corto_replicator_construct(this);
/* $end */
}

corto_resultIter _CarBrands_Connector_onRequest(CarBrands_Connector this, corto_string parent, corto_string expr, corto_bool setContent) {
/* $begin(CarBrands/Connector/onRequest) */

    /* This function is invoked when a select occurs on the scope that the
     * replicator has registered itself for */

    /* Create a persistent iterator (one that does not expire after it runs out
     * of scope). The iterator resources are automatically cleaned up after the
     * iteration is completed. */

    /* In a real life scenario, a replicator could choose to implement its own
     * iterator to tailor the behavior of hasNext and next. */
    return corto_llIterAlloc(this->items);

/* $end */
}
