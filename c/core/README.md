# Core examples
These examples demonstrate the Corto Core API. The Core API is an untyped, dynamic C API that is the foundation for all other APIs in Corto.The Core API is split up into different modules:

## Object API
API for using corto objects.

## Ptr API
API for native pointers.

## Value API
API for dynamic access to corto values.

## Query API
API for querying the store

## Walk API
API for dynamic walking of values.

See https://corto.io/doc/Corto_API_reference.html for the Core API reference.

## Examples
The following list of examples is a non-exhaustive list that, when reviewed in that order, will provide a gentle introduction to the core API.

### objects
Shows the basic API for creating, reading, updating and deleting objects.
**Difficulty**: easy

### objects_hierarchy
Shows how to create objects in a hierarchy.
**Difficulty**: easy

### lookup
Shows how to use the corto_lookup function to search for objects.
**Difficulty**: easy

### error_handling
Shows basic usage of the corto error/logging framework.
**Difficulty**: easy

### observer_simple
Shows how to observe CRUD events for a single object.
**Difficulty**: easy

### observer_hierarchy
Shows how to observe CRUD events for a tree.
**Difficulty** easy

### observer_type
Shows how to observe events for objects of a specific type.
**Difficulty**: easy

### objects_fwddecl
Shows how to use forward declarations to set initial values before notifying observers. Also demonstrates how forward declarations are used to create concurrent applications.
**Difficulty**: moderate

### dynamic_struct
Shows how to use the core API to dynamically create a new struct type, instantiate it, and use the corto_value API to dynamically set the instance.
**Difficulty**: moderate

### dynamic_struct_inheritance
Same as dynamic_struct, but now with inheritance.
**Difficulty**: moderate

### select
Shows how to use the corto_select API to query for objects in the store using different corto id expressions.
**Difficulty**: moderate

### select_contentType
Shows how to use the corto_select API to request results in a specific contentType (JSON). Uses the code from dynamic_struct to instantiate a type to demonstrate JSON serialization.
**Difficulty**: moderate

### subscriber_simple
Shows how to use the corto_subscribe API to do realtime queries. Subscribers are different from observers in that they do not return a reference to an object, which means they can receive notifications even for objects that are not in the in-memory store.
**Difficulty**: easy

### json
Shows how the corto_subscribe and corto_publish API can be used to create an application that does not rely on the in-memory store, but instead just uses JSON values (JSON is just one example of a supported contentType).
**Difficulty**: moderate

### dynamic_call
This example shows how to embed a C function into a corto function object, and then dynamically call it with the corto_call API.
**Difficulty**: moderate

### ownership
Shows how corto ownership works. Ownership is a mechanism that allows corto to determine to which connector ('mount') an object belongs. The example creates a mount class to demonstrate this. The example also creates an 'onNotify' method in the mount class to demonstrate that a mount is not notified of objects that it owns itself.
**Difficulty**: hard

### mount_fibo
This example uses the corto API to create a mount class from scratch. Note that this is significantly easier to do by defining a mount class in a .cx file- this code just serves as an example that it is possible to do dynamically. The mount class that is created serves up the fibonacci sequence. 

The purpose of this example is to demonstrate that a mount in corto can potentially expose infinite datasets without requiring lots of memory. The example also shows how to use the corto_select API to specify an offset/limit for the returned results.
**Difficulty**: hard


