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

Note that the publisher may show a `publish failed` error when starting up. This is because the MQTT connector is connecting asynchronously. Future versions of the corto::mqtt package will resolve this issue.

Both the `Pub` and `Sub` project contain a file called packages.txt in the .corto folder. This ensures that the projects can use the corto::mqtt package. You can use the `corto add <project> <package>` command to add packages to your projects. For example, for these projects these commands were used to add the package to the project:
```
corto add Pub corto::mqtt
corto add Sub corto::mqtt
```
