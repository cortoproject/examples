# HTTP Router Service for Install Requests

Simple example providing an HTTP endpoint for requesting your controller to
install a device. Devices are specified by ID.

A guided explanation of the code is available here,  [https://hendren.xyz/cpp-http-microserver/](https://hendren.xyz/cpp-http-microserver/).

# Example

## Building
```
corto install
```

## Running Example
From project directory:
```
./router
```

**Testing**
Publish POST Request to server:
```
curl -X POST http://localhost:9080/install?device=85
```
Output:
```
info: [oasys/api/install/example] Starting HTTP Router example
info: [oasys/api/install/example] Successfully loaded config [$DIR/install-api.json]
info: [oasys/api/install/example] HTTP.install.httprouter: Received Install Request for Device: [85]
```
