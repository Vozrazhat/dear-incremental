#pragma once

namespace DI {
enum Resource {
    NEURONS = 0,
    MUSCLE_CELLS = 1,
    BIOFLUX = 2,
    // Always should be last. Mild hack lol.
    COUNT_SENTINEL
};
}