/* $CORTO_GENERATED
 *
 * objects_invalid_constructor.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/objects_invalid_constructor.h>

/* $header() */
/* objects_invalid_constructor
 *
 * This example shows advanced usage of creating a class with a constructor that
 * based on the value of an object determines whether it is a valid object or
 * not. If the constructor fails, the object will be invalidated.
 *
 * The example will then show how the constructor will be re-evaluated after the
 * object has been invalidated and redefined.
 *
 * The example shows advanced techniques on how to create a class with the core
 * API. There are easier ways to do this, with definition files and the c-binding
 * (see the c-binding examples).
 */

/* Forward declare member so observer can use it to read the member */
static corto_member myMember;

corto_int16 onConstruct(corto_object this) {
    corto_int32 value = *(corto_int32*)CORTO_OFFSET(this, myMember->offset);
    corto_info("Constructor called, myMember = %d", value);
    return value;
}
/* $end */

int objects_invalid_constructorMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Forward declare a class */
    corto_class myClass = corto_declareChild(root_o, "MyClass", corto_class_o);
    if (!myClass) {
        goto error;
    }

    /* Add a member to the class with type int32 */
    myMember = corto_declareChild(myClass, "myMember", corto_member_o);
    if (!myMember) {
        goto error;
    }

    corto_ptr_setref(&myMember->type, corto_int32_o);
    if (corto_define(myMember)) {
        goto error;
    }

    /* Create constructor */
    corto_method construct = corto_declareChild(myClass, "construct()", corto_method_o);
    if (!construct) {
        goto error;
    }

    /* Constructors should always have an int16 returntype */
    corto_ptr_setref(&corto_function(construct)->returnType, corto_int16_o);
    corto_function(construct)->kind = CORTO_PROCEDURE_CDECL;
    corto_function(construct)->fptr = (corto_word)onConstruct;
    if (corto_define(construct)) {
        goto error;
    }

    /* Finalize class */
    if (corto_define(myClass)) {
        goto error;
    }

    /* Now create an instance with our new class. This invokes our constructor.
     * The constructor will fail if we set our member to a non-zero value, which
     * will invalidate the instance. We'll first make the constructor fail. */
    corto_object instance = corto_declareChild(root_o, "instance", myClass);
    if (!instance) {
        goto error;
    }

    /* Set the value of 'myMember' with metadata */
    *(int32_t*)CORTO_OFFSET(instance, myMember->offset) = -1;

    /* Define our instance. This invokes the constructor. Because myMember
     * is set to -1, and the constructor returns myMember, the corto_define
     * call will fail */
    corto_info("corto_define returns: %d (expect -1)", corto_define(instance));

    /* Show that object is currently invalid */
    corto_info("object is %svalid",
      corto_checkState(instance, CORTO_VALID) ? "" : "not ");

    if (!corto_checkState(instance, CORTO_DEFINED)) {
        /* Try again to validate the object, this time with valid data */
        *(int32_t*)CORTO_OFFSET(instance, myMember->offset) = 0;

        /* Define our instance again. Now corto_define won't fail because the
         * constructor is going to return a valid value. */
        corto_info("corto_define returns: %d (expect 0)", corto_define(instance));
    }

    /* Show that object is now invalid */
    corto_info("object is %svalid",
      corto_checkState(instance, CORTO_VALID) ? "" : "not ");

    /* Objects are automatically deleted... */

    return 0;
error:
    corto_error("error: %s", corto_lasterr());
    return -1;
/* $end */
}
