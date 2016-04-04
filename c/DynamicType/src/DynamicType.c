#include "DynamicType.h"

int DynamicTypeMain(int argc, char *argv[]) {

    /* Create a new struct type */
    corto_structDeclareChild_auto(NULL, Point);
    corto_memberCreateChild_auto(Point, x, corto_int32_o, 0);
    corto_memberCreateChild_auto(Point, y, corto_int32_o, 0);
    corto_structDefine(Point, NULL, 0);

    /* Create an object with the struct type */
    corto_object p = corto_createChild(NULL, "p", Point);

    /* Dynamically assign a value to it */
    corto_fromStr(&p, "{10, 20}");

    /* Print the value to the console */
    corto_string value = corto_str(p, 0);
    printf("value of %s is %s\n", corto_idof(p), value);
    corto_dealloc(value);

    return 0;
}
