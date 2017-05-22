/* $CORTO_GENERATED
 *
 * struct.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/inheritance.h>

/* $header() */
/* Simple example that shows how to model and use a struct with inheritance. */
/* $end */

int inheritanceMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create new instance of struct type with inheritance. Notice that the
     * members of the base-struct are automatically added to the Create.
     */
    inheritance_Point3D *p = inheritance_Point3DCreate(10, 20, 30);
    if (!p) {
        goto error;
    }

    /* Members from the base class can be accessed with 'super' */
    corto_info("p->x = %d, p->y = %d, p->z = %d", p->super.x, p->super.y, p->z);

    /* Send update notification for new value */
    inheritance_Point3DUpdate(p, 20, 30, 40);

    /* An alternative way to get members from a base class is with a cast. In
     * debug mode, this cast will perform a type check. If the casted value is
     * not of the specified type, the application will assert. */
    corto_info("p->x = %d, p->y = %d, p->z = %d", 
        inheritance_Point(p)->x, inheritance_Point(p)->y, p->z);
 
    corto_delete(p);

    return 0;
error:
    return -1;
/* $end */
}
