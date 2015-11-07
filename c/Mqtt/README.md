This example shows how to use the Corto MQTT connector. To run the example you
need to install the `corto::mqtt` package, by running:
```
$ corto install corto::mqtt
```

The example consists out of two projects, Pub and Sub. These are two separate
executables which publish and subscribe to the Corto MQTT broker (you can easily
use your own broker by replacing the address in the code).

To run the projects, do:
```
$ corto run Pub &
$ corto run Sub &
```

The output will look like this:
```
...
[pub] updated value of a to 8
[sub] a updated with value 8
[pub] updated value of a to 9
[sub] a updated with value 9
[pub] updated value of a to 10
[sub] a updated with value 10
...
```

Note that the publisher may show a `publish failed` error when starting up. This is because the MQTT connector is connecting asynchronously. Future versions of the connector will resolve this issue.
