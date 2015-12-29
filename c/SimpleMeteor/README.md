This project requires both Meteor and the Corto web package to be installed. To install both, do:
```
$ curl https://install.meteor.com | sh
$ corto install corto/web
```

To run the project, either type `corto run` from the project directory, or
`corto run <path to project>`.

You also need to start meteor, by running `meteor` from the project directory.

The output will look like this:
```
$ cd SimpleMeteor
$ meteor &
[[[[[ ~/GitHub/cortoproject/examples/c/SimpleMeteor ]]]]]

=> Started proxy.                             
=> Started MongoDB.                           
=> Started your app.                          

=> App running at: http://localhost:3000/

$ corto run
livingRoom = 72.544937, bedRoom = 68.844559, garden = 49.398758
livingRoom = 72.697105, bedRoom = 68.382195, garden = 49.391563
livingRoom = 72.783943, bedRoom = 67.914635, garden = 49.079536
livingRoom = 72.563423, bedRoom = 67.622841, garden = 48.936127
livingRoom = 72.264610, bedRoom = 67.531334, garden = 48.984253
```

Open a browser to `http://localhost:3000` to see the result.
