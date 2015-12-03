/* $CORTO_GENERATED
 *
 * FileBrowser_Connector.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include "FileBrowser.h"

corto_int16 _FileBrowser_Connector_construct(FileBrowser_Connector this) {
/* $begin(FileBrowser/Connector/construct) */
    return corto_replicator_construct(this);
/* $end */
}

/* $header(FileBrowser/Connector/onRequest) */
/* Custom release function that cleans up resultList */
void FileBrowser_Connector_iterRelease(corto_iter *iter) {
    corto_llIter_s *data = iter->udata;
    corto_resultListClear(data->list);
    corto_llFree(data->list);
    corto_llIterRelease(iter);
}
/* $end */
corto_resultIter _FileBrowser_Connector_onRequest(FileBrowser_Connector this, corto_string parent, corto_string expr) {
/* $begin(FileBrowser/Connector/onRequest) */
    corto_id path;
    corto_ll data = corto_llNew(); /* Will contain result of request */
    corto_iter result;

    /* Obtain list of files from 'parent' relative to path */
    sprintf(path, "%s/%s", this->path ? this->path : ".", parent);
    corto_ll dirs = corto_opendir(path);

    /* Walk files, add files to result */
    if (dirs) {
        corto_iter iter = corto_llIter(dirs);
        while (corto_iterHasNext(&iter)) {
            corto_string f = corto_iterNext(&iter);
            corto_resultSet(
                corto_resultListAppendAlloc(data),
                f,
                parent,
                "/FileBrowser/File"
            );
        }

        /* Free up resources of opendir */
        corto_closedir(dirs);
    }

    /* Allocate persistent allocator. Set a custom release function so that the
     * returned list is cleaned up after select is done iterating. */
    result = corto_llIterAlloc(data);
    result.release = FileBrowser_Connector_iterRelease;

    return result;
/* $end */
}
