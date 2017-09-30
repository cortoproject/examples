/* This is a managed file. Do not delete this comment. */

#include <include/resume.h>

int16_t resume_DemoMount_construct(
    resume_DemoMount this)
{
    /* Populate the mount with some demo data */
    corto_resultAssign(
        corto_resultListAppendAlloc(this->data),
        "foo",                      /* id */
        NULL,                       /* name */
        ".",                        /* parent */
        "int32",                    /* type */
        (corto_word)"10",           /* value */
        CORTO_RESULT_LEAF           /* does object have children */
    );

    corto_resultAssign(
        corto_resultListAppendAlloc(this->data),
        "bar",                      /* id */
        NULL,                       /* name */
        ".",                        /* parent */
        "string",                   /* type */
        (corto_word)"\"Hello World\"",  /* value */
        CORTO_RESULT_LEAF           /* does object have children */
    );

    return corto_super_construct(this);
}

corto_object resume_DemoMount_onResume(
    resume_DemoMount this,
    corto_string parent,
    corto_string id,
    corto_object object)
{
    corto_result *r = NULL;
    corto_object result = NULL;
    corto_type type = NULL;

    /* Check if specified id appears in list of objects */
    corto_iter it = corto_ll_iter(this->data);
    while (corto_iter_hasNext(&it)) {
        corto_result *e = corto_iter_next(&it);
        if (!strcmp(e->id, id)) {
            r = e;
            break;
        }
    }

    if (r) {
        /* A result for object was found */

        /* Resolve type of object */
        type = corto_resolve(NULL, r->type);
        if (!type) {
            corto_error("type '%s' not found for object '%s'", r->type, id);
            goto error;
        }

        if (!object) {
            /* When onResume is called when creating a new object, the object
             * already exists in the store. When the application is doing a
             * lookup, the object doesn't exist yet and we have to create it. */

            /* Declare object */
            result = corto_declareChild(NULL, strarg("%s/%s", parent, id), type);
            if (!result) {
                corto_error("failed to create '%s': %s", id, corto_lasterr());
                goto error;
            }
        } else {
            /* When onResume is called with an existing object, check if object 
             * type matches type in mount. */
            if (type != corto_typeof(object)) {
                corto_error("type '%s' of object '%s' does not match with type '%s' in mount",
                    corto_fullpath(NULL, corto_typeof(object)),
                    corto_fullpath(NULL, object),
                    corto_fullpath(NULL, type));
                goto error;
            }
        }

        if (!object) {
            object = result;
        }

        /* Deserialize value into object using the content type of the subscriber
         * class (mount inherits from subscriber). */
        if (corto_fromcontent(object, corto_subscriber(this)->contentType, (void*)r->value)) {
            goto error;
        }

        /* Define object if it's new */
        if (result) {
            if (corto_define(result)) {
                goto error;
            }
        }
    }

    return object;
error:
    /* Clean up */
    if (type) {
        corto_release(type);
    }
    if (result) {
        corto_delete(result);
    }
    return NULL;
}



