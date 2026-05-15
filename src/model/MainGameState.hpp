#pragma once
#include <algorithm>

#include "ResourceManager.hpp"

namespace DI {
class MainGameState {
public:
    MainGameState() = default;
    ~MainGameState() = default;

    double getValue(Resource r) { return resource_manager_.getResourceRef(r); };
    // Pass "delta" seconds.
    void process(float delta);

private:
    ResourceManager resource_manager_{};
    double tickspeed_{1.0};
};
} // namespace DI
