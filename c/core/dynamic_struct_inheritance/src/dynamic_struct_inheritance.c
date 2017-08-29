
#include <include/dynamic_struct_inheritance.h>

/** dynamic_struct_inheritance
 *
 * This example shows how to dynamically create structs with inheritance.
 */

/* Types that match struct definitions */
typedef struct Point_t {
    corto_int32 x;
    corto_int32 y;
} Point_t;

typedef struct Point3D_t {
    Point_t super;
    corto_int32 z;
} Point3D_t;

int dynamic_struct_inheritanceMain(int argc, char *argv[]) {

    /* Create a new struct */
    corto_struct Point = corto_declareChild(root_o, "Point", corto_struct_o);
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

    /* Create struct that inherits from Point */
    corto_struct Point3D = corto_declareChild(root_o, "Point3D", corto_struct_o);
        if (!Point) goto error;

        /* Set base member of baseclass (interface) to Point */
        corto_ptr_setref(&corto_interface(Point3D)->base, Point);

        /* Create z member */
        corto_member z = corto_declareChild(Point3D, "z", corto_member_o);
            if (!z) goto error;
            corto_ptr_setref(&z->type, corto_int32_o);
            if (corto_define(z)) goto error;

        /* Finalize Point3D */
        if (corto_define(Point3D)) goto error;

    /* Create a heap segment large enough for Point */
    Point_t *p = corto_ptr_new(Point);
    if (!p) {
        goto error;
    }

    p->x = 10;
    p->y = 20;

    char *p_str = corto_ptr_contentof(p, Point, "text/corto");
    corto_info("p = %s", p_str);
    corto_dealloc(p_str);
    corto_ptr_free(p, Point3D);

    /* Create an instance of Point3D */
    Point3D_t *p3d = corto_ptr_new(Point3D);
    if (!p3d) {
        goto error;
    }

    p3d->super.x = 10;
    p3d->super.y = 20;
    p3d->z = 30;

    char *p3d_str = corto_ptr_contentof(p3d, Point3D, "text/corto");
    corto_info("p3d = %s", p3d_str);
    corto_dealloc(p3d_str);
    corto_ptr_free(p3d, Point3D);

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
