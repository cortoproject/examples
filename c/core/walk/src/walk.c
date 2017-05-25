/* $CORTO_GENERATED
 *
 * walk.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/walk.h>

/* $header() */
/* This example shows how to use the corto_walk API to dynamically walk the
 * value of a corto object.
 */

corto_struct Point, Line; /* Struct types */

/* Instantiate a few types so we have something to walk over */
int16_t createTypes(void) {
    /* Create a Point struct */
    Point = corto_declareChild(root_o, "Point", corto_struct_o);
        if (!Point) goto error;

        /* Create x member */
        corto_member x = corto_declareChild(Point, "x", corto_member_o);
            if (!x) goto error;
            corto_ptr_setref(&x->type, corto_int32_o);
            if (corto_define(x)) goto error;

        /* Create y member */
        corto_member y = corto_declareChild(Point, "y", corto_member_o);
            if (!y) goto error;
            corto_ptr_setref(&y->type, corto_int32_o);
            if (corto_define(y)) goto error;

        /* Finalize struct */
        if (corto_define(Point)) goto error;

    /* Create a Line struct */
    Line = corto_declareChild(root_o, "Line", corto_struct_o);
        if (!Line) goto error;

        /* Create start member */
        corto_member start = corto_declareChild(Line, "start", corto_member_o);
            if (!start) goto error;
            corto_ptr_setref(&start->type, Point);
            if (corto_define(start)) goto error;

        /* Create stop member */
        corto_member stop = corto_declareChild(Line, "stop", corto_member_o);
            if (!stop) goto error;
            corto_ptr_setref(&stop->type, Point);
            if (corto_define(stop)) goto error;

        /* Finalize struct */
        if (corto_define(Line)) goto error;

    return 0;
error:
    return -1;
}

/* Print primitive value */
int16_t walk_primitive(corto_walk_opt *opt, corto_value *info, void *userData) {
    void *ptr = corto_value_ptrof(info);
    corto_type type = corto_value_typeof(info);
    
    char *str = corto_ptr_contentof(ptr, type, "text/corto");
    printf("%s", str);
    corto_dealloc(str);

    return 0;
}

/* Print reference value */
int16_t walk_reference(corto_walk_opt *opt, corto_value *info, void *userData) {
    void *ptr = corto_value_ptrof(info);
    
    printf("%s", corto_fullpath(NULL, *(corto_object*)ptr));

    return 0;
}

/* Print composite / collection value */
int16_t walk_complex(corto_walk_opt *opt, corto_value *info, void *userData) {
    corto_type type = corto_value_typeof(info);
    uint32_t *indent = userData, needsIndent = 0;
    void *ptr = corto_value_ptrof(info);
    bool isComposite = type->kind == CORTO_COMPOSITE;

    if (info->kind != CORTO_MEMBER) {
        needsIndent = *indent;
    }

    uint64_t count = corto_ptr_count(ptr, type);
    printf("%*s{%s", needsIndent, "", count ? "\n" : "");
    (*indent) += 2;

    if (isComposite) {
        if (corto_walk_members(opt, info, userData)) {
            goto error;
        }
    } else {
        if (corto_walk_elements(opt, info, userData)) {
            goto error;
        }
    }

    (*indent) -= 2;
    printf("%*s}", count ? *indent : 0, "");

    if (info->kind != CORTO_MEMBER) {
        printf("\n");
    }

    return 0;
error:
    return -1;
}

/* Print members and elements */
int16_t walk_item(corto_walk_opt *opt, corto_value *info, void *userData) {
    uint32_t *indent = userData;

    if (info->kind == CORTO_MEMBER) {
        printf("%*s%s = ", *indent, "", corto_idof(info->is.member.t));
    } else if (info->kind == CORTO_ELEMENT) {
        printf("%*s%d = ", *indent, "", info->is.element.t.index);
    }

    if (corto_walk_value(opt, info, userData)) {
        goto error;
    }

    printf("\n");

    return 0;
error:
    return -1;
}

/* Print object */
int16_t walk_object(corto_walk_opt *opt, corto_value *info, void *userData) {
    corto_object o = corto_value_objectof(info);

    printf("%s = ", corto_fullpath(NULL, o));

    if (corto_walk_value(opt, info, userData)) {
        goto error;
    }

    printf("\n");

    return 0;
error:
    return -1;
}

/* $end */

int walkMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create types for our object */
    if (createTypes()) {
        goto error;
    }

    /* Create object with Line type */
    corto_object line = corto_createChild(root_o, "myLine", Line);
    if (!line) {
        goto error;
    }

    /* Initialize object value */
    corto_fromcontent(line, "text/corto", "{{10,20},{30,40}}");

    /* The walk API uses a number of callbacks that are invoked when a value of
     * a specific kind (object, member, element) or type (primitive, composite,
     * collection) is encountered. Set callbacks here. */
    corto_walk_opt opt;
    corto_walk_init(&opt);

    /* Callbacks for different kinds of types */
    opt.program[CORTO_PRIMITIVE] = walk_primitive;
    opt.program[CORTO_COMPOSITE] = walk_complex;
    opt.program[CORTO_COLLECTION] = walk_complex;
    opt.reference = walk_reference;

    /* Callbacks for different kinds of values */
    opt.metaprogram[CORTO_OBJECT] = walk_object;
    opt.metaprogram[CORTO_MEMBER] = walk_item;
    opt.metaprogram[CORTO_ELEMENT] = walk_item;

    /* Call walk, pass indentation variable as state */
    uint32_t indent = 0;
    if (corto_walk(&opt, line, &indent)) {
        goto error;
    }

    /* Call walk again on built-in object */
    indent = 0;
    if (corto_walk(&opt, corto_string_o, &indent)) {
        goto error;
    }

    return 0;
error:
    corto_error("%s", corto_lasterr());
    return -1;
/* $end */
}
