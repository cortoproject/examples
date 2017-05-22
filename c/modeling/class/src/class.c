/* $CORTO_GENERATED
 *
 * class.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/class.h>

/* $header() */
/* Enter code outside of main here. */
/* $end */

int classMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Create a new dog instance. Notice that because Dog inherits from Animal,
     * the Animal/hunger member shows up in the Dog Create function. */
    class_Dog lassie = class_DogCreateChild(root_o, "Lassie", 100);

    /* Feed the dog */
    class_Animal_eat(lassie);
    class_Animal_eat(lassie);
    class_Animal_eat(lassie);

    corto_delete(lassie);

    return 0;
/* $end */
}
