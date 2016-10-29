#include "Notifications.h"

/*
 * This example demonstrates various events that can be subscribed for. The used
 * event masks are:
 *
 * ON_DECLARE: forward declaration- value should not be interpreted.
 * ON_DEFINE: object is created and value may be interpreted.
 * ON_UPDATE: the value of the object changed
 * ON_DELETE: the object is deleted
 *
 * ON_SCOPE: only immediate children of the observable will notify an observer
 * ON_TREE: all descendants of the observable will notify an observer
 *
 * When neither ON_SCOPE or ON_TREE is provided, ON_SELF is automatically added.
 * ON_SELF only triggers on events of the observable itself.
 */

void onUpdateScope(corto_object this, corto_eventMask mask, corto_object observable, corto_observer observer) {
    /* Serialize the value of the observable to a string. The '0' indicates
     * the maximum length of the string, where 0 means no limit. */
    corto_string value = corto_str(observable, 0);

    printf("onUpdateScope: object %s updated (value = %s)\n",
        corto_idof(observable),
        value);

    corto_dealloc(value);
}

void onUpdateTree(corto_object this, corto_eventMask mask, corto_object observable, corto_observer observer) {
    corto_string value = corto_str(observable, 0);

    printf("onUpdateTree: object %s updated (value = %s)\n",
        corto_idof(observable),
        value);

    corto_dealloc(value);
}

void onDeclareTree(corto_object this, corto_eventMask mask, corto_object observable, corto_observer observer) {
    printf("onDeclareTree: object %s declared\n",
        corto_fullpath(NULL, observable));
}

void onDefineTree(corto_object this, corto_eventMask mask, corto_object observable, corto_observer observer) {
    corto_string value = corto_str(observable, 0);

    printf("onDefineTree: object %s defined (value = %s)\n",
        corto_idof(observable),
        value);

    corto_dealloc(value);
}

void onDeleteTree(corto_object this, corto_eventMask mask, corto_object observable, corto_observer observer) {
    printf("onDeleteScope: object %s deleted\n",
        corto_idof(observable));
}

int NotificationsMain(int argc, char *argv[]) {

    /* Create an observer that triggers on declare events in the scope under root */
    corto_observer on_declareTree = corto_observe (CORTO_ON_DECLARE | CORTO_ON_SCOPE, root_o)
        .callback(onDeclareTree);

    /* Create an observer that triggers on define events in the scope under root */
    corto_observer on_defineTree = corto_observe (CORTO_ON_DEFINE | CORTO_ON_SCOPE, root_o)
        .callback(onDefineTree);

    /* Create an observer that triggers on update events in the tree under root */
    corto_observer on_updateTree = corto_observe (CORTO_ON_UPDATE | CORTO_ON_TREE, root_o)
            .callback(onUpdateTree);

    /* Create an observer that triggers on delete events in the tree under root */
    corto_observer on_deleteTree = corto_observe (CORTO_ON_DELETE | CORTO_ON_TREE, root_o)
            .callback(onDeleteTree);

    /* Create an observer that triggers on update events in the scope of root */
    corto_observer on_updateScope = corto_observe (CORTO_ON_UPDATE | CORTO_ON_SCOPE, root_o)
            .callback(onUpdateScope);

    /* Create 'a' in the root, and 'b' in the scope of 'a' */
    corto_int32 *a = corto_int32CreateChild(NULL, "a", 10);
    corto_int32 *b = corto_int32CreateChild(a, "b", 10);

    /* Update a and b with a new value */
    corto_int32Update(a, 20);
    corto_int32Update(b, 20);

    corto_delete(a);
    // B is deleted by a

    /* Cleanup observers */
    corto_delete(on_declareTree);
    corto_delete(on_defineTree);
    corto_delete(on_updateTree);
    corto_delete(on_deleteTree);
    corto_delete(on_updateScope);

    return 0;
}
