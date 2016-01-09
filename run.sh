
testexamples() {

set -e
set -u

corto run c/Crud
corto run c/DynamicType
corto run c/HelloWorld
corto run c/Notifications
corto run c/Select

}

testexamples
