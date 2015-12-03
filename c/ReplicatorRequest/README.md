This project shows how to create a simple replicator that integrates with `corto_select`. 

It contains of two projects, 'App' and 'Replicator'. 
The Replicator project is a package that contains the replicator. The App project uses the Replicator package
and shows how to use `corto_select` with a custom replicator.

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
