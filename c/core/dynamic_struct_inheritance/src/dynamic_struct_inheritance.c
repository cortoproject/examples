#include "dynamic_struct_inheritance.h"

/* dynamic_struct_inheritance
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
    if (!Point) {
        goto error;
    }

    /* Create x member */
    corto_member x = corto_declareChild(Point, "x", corto_member_o);
    if (!x) {
        goto error;
    }
    if (!corto_checkState(x, CORTO_DEFINED)) {
        corto_setref(&x->type, corto_int32_o);
        if (corto_define(x)) {
            goto error;
        }
    }

    /* Create y member */
    corto_member y = corto_declareChild(Point, "y", corto_member_o);
    if (!y) {
        goto error;
    }
    if (!corto_checkState(y, CORTO_DEFINED)) {
        corto_setref(&y->type, corto_int32_o);
        if (corto_define(y)) {
            goto error;
        }
    }

    /* Finalize Point */
    if (corto_define(Point)) {
        goto error;
    }

    /* Create struct that inherits from Point */
    corto_struct Point3D = corto_declareChild(root_o, "Point3D", corto_struct_o);
    if (!Point) {
        goto error;
    }

    /* Create x member */
    corto_member z = corto_declareChild(Point3D, "z", corto_member_o);
    if (!z) {
        goto error;
    }
    if (!corto_checkState(z, CORTO_DEFINED)) {
        corto_setref(&z->type, corto_int32_o);
        if (corto_define(z)) {
            goto error;
        }
    }

    /* Set base member of baseclass (interface) to Point */
    corto_setref(&corto_interface(Point3D)->base, Point);

    /* Finalize Point3D */
    if (corto_define(Point3D)) {
        goto error;
    }

    /* Create an instance of Point */
    Point_t *p = corto_createChild(root_o, "p", Point);
    if (!p) {
        goto error;
    }

    p->x = 10;
    p->y = 20;
    printf("p = %s\n", corto_contentof(NULL, "text/corto", p));

    /* Create an instance of Point3D */
    Point3D_t *p3d = corto_createChild(root_o, "p3d", Point3D);
    if (!p) {
        goto error;
    }

    p3d->super.x = 10;
    p3d->super.y = 20;
    p3d->z = 30;
    printf("p3d = %s\n", corto_contentof(NULL, "text/corto", p3d));

    /* The instanceof function takes into account inheritance */
    printf("p instanceof Point = %s\n", corto_instanceof(Point, p) ? "true" : "false");
    printf("p instanceof Point3D = %s\n", corto_instanceof(Point3D, p) ? "true" : "false");
    printf("p3d instanceof Point = %s\n", corto_instanceof(Point, p3d) ? "true" : "false");
    printf("p3d instanceof Point3D = %s\n", corto_instanceof(Point3D, p3d) ? "true" : "false");

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
}
