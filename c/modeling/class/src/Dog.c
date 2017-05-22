/* $CORTO_GENERATED
 *
 * Dog.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/class.h>

int16_t _class_Dog_construct(
    class_Dog this)
{
/* $begin(class/Dog/construct) */
    char *str = corto_contentof(this, "text/json");
    corto_info("Dog construct invoked with value %s", str);
    corto_dealloc(str);

    class_Animal(this)->canFly = false;

    /* Call constructor of super class */
    return corto_super_construct(this);
/* $end */
}

void _class_Dog_destruct(
    class_Dog this)
{
/* $begin(class/Dog/destruct) */

    corto_info("Dog destruct invoked");

    /* Call destructor of super class */
    corto_super_destruct(this);

/* $end */
}

void _class_Dog_eat(
    class_Dog this)
{
/* $begin(class/Dog/eat) */

    class_Animal(this)->hunger -= 10;
    corto_info("Dog eat invoked (hunger = %d)", class_Animal(this)->hunger);

/* $end */
}
