/* This is a managed file. Do not delete this comment. */

#include <include/class.h>


/* Enter code outside of main here. */

int classMain(int argc, char *argv[]) {

    /* Create a new dog instance. Notice that because Dog inherits from Animal,
     * the Animal/hunger member shows up in the Dog Create function. */
    class_Dog lassie = class_DogCreateChild(root_o, "Lassie", 100);

    /* Feed the dog */
    class_Animal_eat(lassie);
    class_Animal_eat(lassie);
    class_Animal_eat(lassie);

    corto_delete(lassie);

    return 0;
}

