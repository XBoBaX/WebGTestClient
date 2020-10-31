A C++ client library for Selenuim Driver

## Install with tests
If you want to test it all out through the common gtest procedure, first delete build/ (if present). Then...

```bash
mkdir build
cd build && cmake ..
cmake -Dtest=ON --build .
cmake --build .
```

## Run bin
build/tests/Debug/diplomWork_test.exe

## Run selenium server
Download http://www.seleniumhq.org/download/
Run selenium with host and port
```bash
java -jar selenium-server-standalone-3.141.59.jar -role hub
java -Dwebdriver.chrome.driver=<path_to_driver>\chromedriver.exe -jar selenium-server-standalone-3.141.59.jar -role node -port 7777 -hub http://localhost:4444/grid/register
```