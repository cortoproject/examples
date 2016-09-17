/* $CORTO_GENERATED
 *
 * Security.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <Security/Security.h>

int SecurityMain(int argc, char* argv[]) {
/* $begin(main) */

    /* Create dummy objects */
    corto_voidCreateChild_auto(root_o, a);
    corto_voidCreateChild_auto(a, b);
    corto_voidCreateChild_auto(a, c);
    corto_voidCreateChild_auto(a, d);

    /* Create key object to enable secure authentication */
    Security_MyKeyCreate();

    /* Create lock that denies reading object /a/b for user 'token_user01' */
    Security_MyLock lock = Security_MyLockCreate("/a/b", ".", 0, NULL);
    Security_AccessRule rule = {"token_user01", CORTO_SECURE_ACTION_READ, CORTO_SECURE_ACCESS_DENIED};
    Security_AccessRuleListInsert(lock->rules, &rule);

    /* Login to authenticate user, return token (should be token_user01) */
    corto_string token = corto_login("Ford Prefect", "42");

    /* Set authentication token for current process */
    corto_string prev = corto_authenticate(token);

    /* Loop over objects, should not display 'b' */
    corto_iter it;
    corto_select("/a", "*").iter(&it);
    corto_resultIterForeach(it, r) {
        printf("> %s\n", r.id);
    }

    /* Reset authentication token */
    corto_authenticate(prev);

    return 0;
/* $end */
}
