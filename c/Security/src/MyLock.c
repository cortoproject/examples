/* $CORTO_GENERATED
 *
 * MyLock.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <Security/Security.h>

corto_secure_accessKind _Security_MyLock_authorize(
    Security_MyLock this,
    corto_string token,
    corto_secure_actionKind action)
{
/* $begin(Security/MyLock/authorize) */
    Security_AccessRuleListForeach(this->rules, r) {
        if (!strcmp(r.user, token) && (r.action == action)) {
            return r.access;
        }
    }
    return CORTO_SECURE_ACCESS_UNDEFINED;
/* $end */
}
