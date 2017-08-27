/* This is a managed file. Do not delete this comment. */

#include <include/class.h>

int16_t class_Dog_construct(
    class_Dog this)
{
    char *str = corto_contentof(this, "text/json");
    corto_info("Dog construct invoked with value %s", str);
    corto_dealloc(str);

    class_Animal(this)->canFly = false;

    /* Call constructor of super class */
    return corto_super_construct(this);
}

void class_Dog_destruct(
    class_Dog this)
{

    corto_info("Dog destruct invoked");

    /* Call destructor of super class */
    corto_super_destruct(this);

}

void class_Dog_eat(
    class_Dog this)
{

    class_Animal(this)->hunger -= 10;
    corto_info("Dog eat invoked (hunger = %d)", class_Animal(this)->hunger);

}

