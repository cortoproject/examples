/* This is a managed file. Do not delete this comment. */

#include <include/router.h>

int16_t router_service_construct(
    router_service this)
{
    return corto_super_construct(this);
}

corto_string router_service_install(
    router_service this,
    httpserver_HTTP_Request *request,
    router_install *data)
{
    corto_string id = httpserver_HTTP_Request_getVar(request, "device");

    if (id == NULL)
    {
        corto_string msg;
        msg = corto_asprintf("400: POST failed: %s: device=%s",
            corto_lasterr(), id);
        httpserver_HTTP_Request_setStatus(request, 400);
        httpserver_HTTP_Request_reply(request, msg);
    }
    else
    {
        httpserver_HTTP_Request_setStatus(request, 200);
        httpserver_HTTP_Request_reply(request, "Ok\n");

        corto_info("Received Install Request for Device ID: [%s]", id);
    }

    return httprouter_route_defaultAction(router_service_install_o, this, request);
}
