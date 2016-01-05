#include "SimpleMeteor.h"

float rnd() { return (float)rand() / (float)RAND_MAX - 0.5; }

int SimpleMeteorMain(int argc, char *argv[]) {

    /* Start a DDP server on port 8000 */
    server_DDPCreateChild(root_o, "ddpx", 8000);

    /* Create a scope (equivalent to a Meteor Collection) */
    corto_object Temperature_o = corto_voidCreateChild(root_o, "Temperature");

    /* Create a few virtual thermometers */
    corto_float32 *livingRoom_o =
      corto_float32CreateChild(Temperature_o, "livingRoom", 72.0);

    corto_float32 *bedRoom_o =
      corto_float32CreateChild(Temperature_o, "bedRoom", 68.0);

    corto_float32 *garden_o =
      corto_float32CreateChild(Temperature_o, "garden", 50.0);

    /* Enter infinite while loop & update objects every second */
    while (1) {
        corto_float32Update(livingRoom_o, *livingRoom_o + rnd());
        corto_float32Update(bedRoom_o, *bedRoom_o + rnd());
        corto_float32Update(garden_o, *garden_o + rnd());

        printf("livingRoom = %f, bedRoom = %f, garden = %f\n",
            *livingRoom_o,
            *bedRoom_o,
            *garden_o);

        corto_sleep(1, 0);
    }

    return 0;
}
