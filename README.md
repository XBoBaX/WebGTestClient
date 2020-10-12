# WebGTestClient

A C++ client library for Selenuim Driver

## Install with tests
If you want to test it all out through the common gtest procedure, first delete build/ (if present). Then...

```bash
mkdir build
cd build && cmake ..
cmake --build .
```

## Command things
cmake -Dtest=ON turns on the variable 'test'

## Run bin
build/tests/Debug/diplomWork_test.exe
