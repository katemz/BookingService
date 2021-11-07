# BookingService

BookingService implements a backend for a service allowing to make reservation for a movie.
It works on the address: <service_address>/api/ [by default 127.0.0.1/api/].

#### Assumptions
- There is max. 1 seance of specific movie for a theater (no time/calendar)
- Movie name is unique
- Theater name is unique
- All theaters have 20 seats

## REST API documentation

Service supports following requests:

### GET

#### Get all movies requests

##### Request
<service_address>/api/getallmovies

##### JSON Response
movies: All movies as string array

`{"movies":[ "movie1", "movie2"...]}`


#### Get all theaters playing specified movie

##### Request
<service_address>/api/gettheatersplayingmovie/<moviename>

#### JSON Response
movie: Specified movie
theaters: All theaters that play movie as string array

`{"movie":"<movie>","theaters":["theater1", "theater2"...]}`


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


