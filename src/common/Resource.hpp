#pragma once

namespace DI {
enum Resource {
    NEURONS = 0,
    MUSCLE_CELLS = 1,
    BIOFLUX = 2,
    // Always should be last. Mild hack lol.
    COUNT_SENTINEL
};

struct ResourceCount {
    // Needed for emplace back fml
    ResourceCount(Resource r, double c) : resource(r), count(c) {}
    Resource resource;
    double count;
};
}