/* $CORTO_GENERATED
 *
 * dynamic_class.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/dynamic_class.h>

/* $header() */
/* dynamic_class
 *
 * This example shows how to dynamically create a new class type. A class is
 * very similar to a struct, except that it is considered a reference type. This
 * means that any instance of a class-type *must* be an object, and are therefore
 * never allocated on the stack.
 *
 * This example also demonstrates how to dynamically create a constructor,
 * destructor and method.
 */

 /* Type that matches the class definition */
typedef struct Point_t {
    corto_int32 x;
    corto_int32 y;
} Point_t;

/* Constructor */
corto_int16 Point_construct(Point_t *this) {
    char *str = corto_contentof(this, "text/corto");
    corto_info("%s: construct '%s'", corto_idof(this), str);
    corto_dealloc(str);
    /* Return success */
    return 0;
}

/* Destructor */
void Point_destruct(Point_t *this) {
    corto_info("%s: destruct", corto_idof(this));
}

/* Add method */
void Point_add(Point_t *this, Point_t *p) {
    this->x += p->x;
    this->y += p->y;
}
/* $end */

int dynamic_classMain(int argc, char *argv[]) {
/* $begin(main) */
    /* Create a new class */
    corto_class Point = corto_declareChild(root_o, "Point", corto_class_o);
    if (!Point) {
        goto error;
    }

    /* Create x member */
    corto_member x = corto_declareChild(Point, "x", corto_member_o);
    if (!x) {
        goto error;
    }
    if (!corto_checkState(x, CORTO_VALID)) {
        corto_ptr_setref(&x->type, corto_int32_o);
        if (corto_define(x)) {
            goto error;
        }
    }

    /* Create y member */
    corto_member y = corto_declareChild(Point, "y", corto_member_o);
    if (!y) {
        goto error;
    }
    if (!corto_checkState(y, CORTO_VALID)) {
        corto_ptr_setref(&y->type, corto_int32_o);
        if (corto_define(y)) {
            goto error;
        }
    }

    /* Create constructor.
     *
     * Constructors are called by corto_define, *after* the value of the object
     * has been set. The implementation of the constructor is entirely driven by
     * the value of the object. This fits the data centric design of Corto where
     * behavior is encapsulated by data, instead of the other way around (OOP).
     */
    corto_method construct = corto_declareChild(Point, "construct()", corto_method_o);
    if (!construct) {
        goto error;
    }
    if (!corto_checkState(construct, CORTO_VALID)) {
        /* Constructors in corto must return a zero (ok) or nonzero (nok)
         * returncode to indicate whether construction was successful. If the
         * constructor fails, the object will be marked invalid after which the
         * application can retry to define the object.
         *
         * The `returnType` member is from the baseclass of method (function).
         */
        corto_ptr_setref(&corto_function(construct)->returnType, corto_int16_o);

        /* Bind the object with a C function */
        corto_function(construct)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(construct)->fptr = (corto_word)Point_construct;

        if (corto_define(construct)) {
            goto error;
        }
    }

    /* Create destructor */
    corto_method destruct = corto_declareChild(Point, "destruct()", corto_method_o);
    if (!destruct) {
        goto error;
    }
    if (!corto_checkState(destruct, CORTO_VALID)) {
        /* Bind the object with a C function */
        corto_function(destruct)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(destruct)->fptr = (corto_word)Point_destruct;
        if (corto_define(destruct)) {
            goto error;
        }
    }

    /* Create add method.
     *
     * The function signature is part of the object id. This is because corto
     * supports method overloading, and the signature in the id helps tell the
     * different overloaded functions apart.
     */
    corto_method add = corto_declareChild(Point, "add(Point p)", corto_method_o);
    if (!add) {
        goto error;
    }
    if (!corto_checkState(add, CORTO_VALID)) {
        /* Bind the object with a C function */
        corto_function(add)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(add)->fptr = (corto_word)Point_add;
        if (corto_define(add)) {
            goto error;
        }
    }

    /* Finalize class */
    if (corto_define(Point)) {
        goto error;
    }

    /* Create instance of Point with default values */
    Point_t *p1 = corto_createChild(root_o, "p1", Point);
    if (!p1) {
        goto error;
    }

    /* Create instance of Point with initial values */
    Point_t *p2 = corto_declareChild(root_o, "p2", Point);
    if (!p2) {
        goto error;
    }
    if (!corto_checkState(p2, CORTO_VALID)) {
        p2->x = 10;
        p2->y = 20;

        /* This will call the constructor for p2 */
        if (corto_define(p2)) {
            goto error;
        }
    }

    /* Call add method twice */
    corto_call(add, NULL, p1, p2);
    corto_call(add, NULL, p1, p2);

    /* Show value of p1 */
    char *str = corto_contentof(p1, "text/corto");
    corto_info("p1 after add: '%s'", str);
    corto_dealloc(str);

    /* Notice that destructors are called when application exits. Objects in the
     * hierarchy are automatically cleaned up when exitting. */

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
