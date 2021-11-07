# BookingService

BookingService implements a backend for a service allowing to make reservation for a movie.



# Installation

## Libraries required

* cmake
* pthread
* boost_system
* crypto
* ssl
* **cpprest**

## Build and run
```
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" 
make all
./test/ExampleProject_tst
./src/ExampleProject_run
```


Assumptions:
- There is only 0 or 1 seance for specific movie in given theater (no calendar/time)
- movie name is unique
- theater name is unique




