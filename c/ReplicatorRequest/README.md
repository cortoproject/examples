This project shows how to create a simple replicator that integrates with `corto_select`. 

It contains of two projects, 'App' and 'Replicator'. 
The Replicator project is a package that contains a class which inherits from `corto/lang/replicator`. The
class has a list of items (car brands) which it will feed to select when a request is made.

The App project uses the Replicator package and demonstrates how a custom replicator integrates with `corto_select`.

To run the project, type `rake` from the project directory, followed by `corto run App`.

The output will look like this:
```
$ corto run App
Found Audi of type 'Brand'
Found BMW of type 'Brand'
Found Ford of type 'Brand'
Found Toyota of type 'Brand'
Found Volkswagen of type 'Brand'
```
