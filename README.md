# BookingService

BookingService implements a backend for a service allowing to make reservation for a movie.

It's bound on the address: **<service_address>/api/** (by default **127.0.0.1:8080/api/**).

#### Assumptions
- There is max. 1 show of specific movie for a theater (no time/calendar)
- Movie name is unique
- Theater name is unique
- All theaters have 20 seats

## REST API documentation

Service supports following requests:

### GET

| Request   |      URL      |  JSON return value |
|-----------|:-------------:|:-------------------|
| Get all movies |`<service_address>/api/`<br />`getallmovies`| - movies: all movies as string array <br />`{"movies":[ "movie1", "movie2"...]}`|
| Get all theaters playing specified movie |`<service_address>/api/`<br /> `gettheatersplayingmovie/<moviename>`| - movie: specified movie <br /> - theaters: all theaters that play movie as string array<br />`{"movie":"<movie>","theaters":["theater1", "theater2"...]}` |
| Get available seats for movie in theater | `<service_address>/api/`<br /> `getseatsforseance/<moviename>/<theatername>` | - available_seats: available seats ids as number array<br /> - movie: specified movie<br /> - theater: specified theater<br /> `{"available_seats": [id1, id2, id3...], "movie":"<movie>","theater":"<theater>"}` |
    
### PUT
| Request   |      URL      |  JSON input | Status codes |
|-----------|:-------------:|:-------------------|:-------|
| Reserve seats for show |`<service_address>/api/`<br />`reserve`| - movie: movie to reserve<br /> - theater: theater to reserve<br /> - seats: seats ids to reserve as a number array<br />`{"movie": "<movie>", "theater": "<theater>", "seats": [id1, id2, id3...]`| `status_codes::OK`: successfully reserved <br />`status_codes::BadRequest`: reservation failed (invalid seance or seats already taken) |

***


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

or, from existing repository:

`git submodule update --init --recursive`

## Build and run
```
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" 
make all
```

Run app from BookingService/build directory:
```
./src/BookingService_run
```

Run UT from BookingService/build directory:
```
./test/BookingService_test
```


