# BookingService


apt-get install cmake

cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" 

make all

./test/ExampleProject_tst
./src/ExampleProject_run


Assumptions:
- There is only 0 or 1 seance for specific movie in given theater (no calendar/time)
- movie name is unique
- theater name is unique




sudo apt-get install libcpprest-dev
