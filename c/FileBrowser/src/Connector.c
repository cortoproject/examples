/* $CORTO_GENERATED
 *
 * Connector.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include "FileBrowser/FileBrowser.h"

/* $header() */
#include <sys/stat.h>
#include <errno.h>
/* $end */

corto_int16 _FileBrowser_Connector_construct(FileBrowser_Connector this) {
/* $begin(FileBrowser/Connector/construct) */
    /* Let corto know which serialized format this replicator is using */
    corto_replicator_setContentType(this, "text/json");
    return corto_replicator_construct(this);
/* $end */
}

/* $header(FileBrowser/Connector/onRequest) */
void FileBrowser_Connector_iterRelease(corto_iter *iter) {
    corto_llIter_s *data = iter->udata;

    /* Delete data from request */
    corto_resultListClear(data->list);
    corto_llFree(data->list);

    /* Call iter release function that was overridden by this function */
    corto_llIterRelease(iter);
}
/* $end */
corto_resultIter _FileBrowser_Connector_onRequest(FileBrowser_Connector this, corto_string parent, corto_string expr, corto_string param, corto_bool setContent) {
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
            corto_string value = NULL; /* only used when setContent is TRUE */
            struct stat attr;

            /* Build full path to file from current directory */
            corto_id fpath; sprintf(fpath, "%s/%s", path, f);

            /* Stat file to determine whether it's a directory */
            if (stat(fpath, &attr) < 0) {
                corto_error("failed to stat '%s' (%s)\n",
                    fpath,
                    strerror(errno));
            }

            /* When required, provide object value in JSON */
            if (setContent) {
                char modified[20];

                strftime(
                  modified, 20, "%Y-%m-%d %H:%M:%S", localtime(&attr.st_mtime));

                /* Create JSON */
                corto_asprintf(
                  &value,
                  "{\"size\":%d, \"modified\":\"%s\", \"uid\":%d, \"gid\":%d}",
                  attr.st_size, modified, attr.st_uid, attr.st_gid);
            }

            /* Create and initialize new result element */
            corto_resultSet(
                corto_resultListAppendAlloc(data),
                f, /* Name */
                parent, /* Parent */
                S_ISDIR (attr.st_mode) ? "os/Directory" : "os/File", /* Type */
                (corto_word) value /* Value */
            );
        }

        /* Free up resources of opendir */
        corto_closedir(dirs);
    }

    /* Allocate persistent iterator. Set a custom release function so that the
     * returned list is cleaned up after select is done iterating. */
    result = corto_llIterAlloc(data);
    result.release = FileBrowser_Connector_iterRelease;

    return result;
/* $end */
}
