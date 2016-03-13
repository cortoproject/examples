#include "Rest.h"

int RestMain(int argc, char *argv[]) {

    /* Create a REST service on port 8000 */
    server_RESTCreateChild(root_o, "rest", 8000, "");

    /* Create a few dummy 'temperature' objects */
    corto_object Home_o = corto_voidCreateChild(root_o, "Home");
    corto_float32CreateChild(Home_o, "Bathroom", 72);
    corto_float32CreateChild(Home_o, "Bedroom", 68);
    corto_float32CreateChild(Home_o, "LivingRoom", 71);

    /* Show suggestions to try out */
    printf(
      "REST service is up & running! Try out any of the following URLs:\n\n");

    printf("Show the REST server object:\n");
    printf("  http://localhost:8000/rest\n\n");

    printf("Show all temperature objects:\n");
    printf("   http://localhost:8000/Home?select=*\n\n");

    printf("Show all temperature objects with their value:\n");
    printf("   http://localhost:8000/Home?value=true&select=*\n\n");

    printf("Show all temperature objects with their type:\n");
    printf("   http://localhost:8000/Home?type=true&select=*\n\n");

    printf("Show only the LivingRoom object with value and type:\n");
    printf("   http://localhost:8000/Home/LivingRoom?value=true&type=true\n");

    /* Keep application alive */
    while (1) {
        corto_sleep(1, 0);
    }

    return 0;
}
