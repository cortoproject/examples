/* This is a managed file. Do not delete this comment. */

#include <include/class.h>

int16_t class_Animal_construct(
    class_Animal this)
{

    corto_info("Animal construct invoked");

    /* A zero return indicates success, a non-zero indicates failure. */
    return 0;
}

void class_Animal_destruct(
    class_Animal this)
{

    corto_info("Animal destruct invoked");

}

void class_Animal_eat_v(
    class_Animal this)
{

    corto_info("Animal eat invoked");

}

