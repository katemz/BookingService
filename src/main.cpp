#include <iostream>
#include "BookingServiceEngine.hpp"
#include "VolatileDatabase.hpp"

const std::vector<Movie> ALL_MOVIES = {
    Movie{0, "Dune"},
    Movie{1, "MrHyde"},
    Movie{2, "Batman"},
    Movie{3, "Spiderman"}};

const std::vector<Theater> ALL_THEATERS = {
    Theater{0, "NoweHoryzonty"},
    Theater{1, "Helios"},
    Theater{2, "CinemaCity"}};

const std::vector<Seance> ALL_SEANCES = {
    Seance{0, ALL_MOVIES[1], ALL_THEATERS[0]},
    Seance{1, ALL_MOVIES[0], ALL_THEATERS[0]},
    Seance{2, ALL_MOVIES[2], ALL_THEATERS[0]},
    Seance{3, ALL_MOVIES[2], ALL_THEATERS[1]},
    Seance{4, ALL_MOVIES[0], ALL_THEATERS[2]},
    Seance{5, ALL_MOVIES[3], ALL_THEATERS[2]},
    Seance{6, ALL_MOVIES[3], ALL_THEATERS[1]}
};

int main() {

    auto Database = std::make_shared<VolatileDatabase>();
    Database->addSeances(ALL_SEANCES);

    BookingServiceEngine service("127.0.0.1","8080");
    service.setEndpoint("/api");
    service.accept().wait();

    service.setDatabaseHandler(Database);

    while(true)
    {
        sleep(1000);
    }

    return 0;
}
