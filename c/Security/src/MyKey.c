/* $CORTO_GENERATED
 *
 * MyKey.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <Security/Security.h>

corto_string _Security_MyKey_authenticate(
    Security_MyKey this,
    corto_string user,
    corto_string password)
{
/* $begin(Security/MyKey/authenticate) */
    if (!strcmp(user, "Ford Prefect") && !strcmp(password, "42")) {
        return "token_user01";
    } else
    if (!strcmp(user, "Marvin") && !strcmp(password, "android")) {
        return "token_user02";
    }
    return NULL;
/* $end */
}
