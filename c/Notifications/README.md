This project shows how to generate and subscribe for object lifecycle notifications.

To run the project, either type `corto run` from the project directory, or
`corto run <path to project>`.

The output will look like this:
```
$ corto run Notifications
onDeclareTree: object a declared
onDefineTree: object a defined (value = 10)
onUpdateTree: object a updated (value = 10)
onUpdateScope: object a updated (value = 10)
onDeclareTree: object b declared
onDefineTree: object b defined (value = 10)
onUpdateTree: object b updated (value = 10)
onUpdateTree: object a updated (value = 20)
onUpdateScope: object a updated (value = 20)
onUpdateTree: object b updated (value = 20)
onDeleteScope: object b deleted
onDeleteScope: object a deleted
```
