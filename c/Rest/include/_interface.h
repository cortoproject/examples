/* _interface.h
 *
 * This file contains generated code. Do not modify!
 */

#if BUILDING_REST && defined _MSC_VER
#define REST_DLL_EXPORTED __declspec(dllexport)
#elif BUILDING_REST
#define REST_EXPORT __attribute__((__visibility__("default")))
#elif defined _MSC_VER
#define REST_EXPORT __declspec(dllimport)
#else
#define REST_EXPORT
#endif

