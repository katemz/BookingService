# BookingService

BookingService implements a backend for a service allowing to make reservation for a movie.

It's mounted on the address: **<service_address>/api/** (by default **127.0.0.1/api/**).

#### Assumptions
- There is max. 1 seance of specific movie for a theater (no time/calendar)
- Movie name is unique
- Theater name is unique
- All theaters have 20 seats

## REST API documentation

Service supports following requests:

### GET

***

### Get all movies requests

##### Request
`<service_address>/api/getallmovies`

##### JSON Response
- movies: all movies as string array

`{"movies":[ "movie1", "movie2"...]}`

***

### Get all theaters playing specified movie

##### Request
`<service_address>/api/gettheatersplayingmovie/<moviename>`

##### JSON Response
- movie: specified movie
- theaters: all theaters that play movie as string array

`{"movie":"<movie>","theaters":["theater1", "theater2"...]}`

***

### Get available seats for movie in theater

##### Request
`<service_address>/api/getseatsforseance/<moviename>/<theatername>`

#### JSON Response
- available_seats: available seats ids as number array
- movie: specified movie
- theater: specified theater

`{"available_seats": [id1, id2, id3...], "movie":"<movie>","theater":"<theater>"}`

### PUT

***

#### Request

`<service_address>/api/reserve`

JSON input: 
- movie: movie to reserve
- theater: theater to reserve
- seats: seats ids to reserve as a number array

```
{
    "movie": "<movie>",
    "theater": "<theater>",
    "seats": [id1, id2, id3...]
}
```


#### Response
* Successfully reserved

Returns **status_codes::OK**


* Reservation failed (invalid seance or seats already taken)

Returns **status_codes::BadRequest**

# Installation

## Libraries required

* cmake
* pthread
* boost_system
* crypto
* ssl
* **cpprest**

## Clone
This project includes **gtest** as submodule so to clone it with gtest call:

`git clone --recurse-submodules --remote-submodules git@github.com:katemz/BookingService.git`

## Build and run
```
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" 
make all
./test/ExampleProject_tst
./src/ExampleProject_run
```


