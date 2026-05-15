#pragma once

#include "../model/MainGameState.hpp"
#include "../model/ResourceManager.hpp"

// At the moment just takes a strict gamestate, going to change this to a virtual class later.

namespace DI {
class MainGameViewModel {
public:
    MainGameViewModel(MainGameState &state) : state_(state) {}
    ~MainGameViewModel() = default;

    // double getNeurons() { return state_.getNeurons(); };
    // void incrementNeurons(int amount = 1) { state_.incrementNeurons(amount); };
    double getValue(Resource r) { return state_.getValue(r); }

private:
    MainGameState &state_;
};
} // namespace DI
