/* $CORTO_GENERATED
 *
 * hierarchy.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/hierarchy.h>

/* $header() */
/* This code demonstrates how to use predefined hierarchies. */
/* $end */

int hierarchyMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Forward declare Car */
    hierarchy_Car car = hierarchy_CarDeclareChild(root_o, "myCar");

    /* While the object hasn't been defined yet, we can set its values. */
    corto_ptr_setstr(&car->vin, "randomstring";
    car->color = Hierarchy_Red;
    car->speed = 0;

    /* Lookup the engine, set its values. The lookupAssert function is a special
     * case of corto_lookup, which can be used if an application is sure that
     * the object exists. If it doesn't exist, the function will assert. */
    hierarchy_Car_Engine engine = corto_lookupAssert(
        myCar, "Engine", hierarchy_Car_Engine_o);

    engine->rpm = 0;
    engine->temperature = 0;
    engine->oilLevel = 100;
    engine->fuelLevel = 100;
    engine->warningLight = false;

    /* Don't define the engine yet, it will be automatically defined when the
     * 'myCar' object is defined . */

    /* Create the wheels */
    corto_createChild(myCar, "Wheel/FrontLeft", hierarchy_Car_Wheel_o);
    corto_createChild(myCar, "Wheel/FrontRight", hierarchy_Car_Wheel_o);
    corto_createChild(myCar, "Wheel/RearLeft", hierarchy_Car_Wheel_o);
    corto_createChild(myCar, "Wheel/RearLeft", hierarchy_Car_Wheel_o);

    /* Now we can define the car */
    if (corto_define(car)) {
        goto error;
    }

    return 0;
error:
    return -1;
/* $end */
}
