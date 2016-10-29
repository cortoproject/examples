#include "error_handling.h"

/* error_handling
 *
 * This example shows how basic usage of the error reporting functions in corto.
 */

/* This dummy function demonstrates the idiomatic way of reporting errors in a
 * library function */
corto_int16 dummy_function(int val) {
    if (val != 0) {
        corto_seterr("something went wrong (%d)", val);
        goto error;
    }

    return 0; /* 0 indicates success */
error:
    return -1; /* nonzero indicates error */
}

int error_handlingMain(int argc, char *argv[]) {

    /* Set a verbosity level. Available levels are:
     * DEBUG, TRACE, INFO, OK, WARNING, ERROR, CRITICAL */
    corto_verbosity(CORTO_TRACE);

    /* corto_trace is for logging tracing data CORTO_TRACE. The other available
     * functions for logging are corto_debug, corto_info, corto_ok, corto_warning
     * corto_error and corto_critical. */
    corto_trace("Starting example");

    /* corto_ok is meant to log messages that indicate that a task has finished
     * successfully. */
    corto_ok("Example started");

    /* Warnings are meant to indicate something unexpected is happening */
    corto_warning("About to call a failing function!");

    /* Try out the dummy function */
    if (dummy_function(10)) {
        /* corto_error logs an error message to the console */
        corto_error("dummy_function returned error: %s",
          corto_lasterr()); /* corto_lasterr has the last error for this thread */
    }

    /* Note that when a function fails, an application *MUST* use corto_lasterr
     * to 'catch' the error. Corto will otherwise assume that the error has gone
     * unnoticed, and will (eventually) report an error to the command line. */

    return 0;
}
