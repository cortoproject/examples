/* This is a managed file. Do not delete this comment. */

#include <include/lifecycle.h>

static void echo(lifecycle_Foo this, char* hook) {
    corto_state s = corto_stateof(this);
    char *stateStr = corto_ptr_str(&s, corto_state_o, 0);
    corto_info("callback: %s [%s]", 
        hook,
        stateStr);
    free(stateStr);
}

int16_t lifecycle_Foo_construct(
    lifecycle_Foo this)
{
    echo(this, "construct");
    return 0;
}

void lifecycle_Foo_define(
    lifecycle_Foo this)
{
    echo(this, "define");
}

void lifecycle_Foo_deinit(
    lifecycle_Foo this)
{
    echo(this, "deinit");
}

void lifecycle_Foo_delete(
    lifecycle_Foo this)
{
    echo(this, "delete");
}

void lifecycle_Foo_destruct(
    lifecycle_Foo this)
{
    echo(this, "destruct");
}

int16_t lifecycle_Foo_init(
    lifecycle_Foo this)
{
    echo(this, "init");
    return 0;
}

void lifecycle_Foo_update(
    lifecycle_Foo this)
{
    echo(this, "update");
}

int16_t lifecycle_Foo_validate(
    lifecycle_Foo this)
{
    echo(this, "validate");
    return 0;
}

