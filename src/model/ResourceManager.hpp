#pragma once
#include <array>
#include <vector>

#include "../common/Resource.hpp"

namespace DI {
enum SlotType { BASE = 0, MULT = 1, EXP = 2 };

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager() = default;

    // Gets the reference to a particular resource value for reading.
    const double &getResourceRef(Resource r) { return resource_values_.at(static_cast<int>(r)); };
    // Adds a new value to the requested slot and returns a writeable reference to it.
    double &requestSlot(Resource r, SlotType t);
    void process(float delta);

private:
    std::vector<double> resource_values_ = std::vector<double>(static_cast<int>(Resource::COUNT_SENTINEL), 0.0);
    // A vector of resources, each of which is an array (base, mult, exp), which are vectors maintained by upgrades
    std::vector<std::array<std::vector<double>, 3>> resource_vps_ = std::vector<std::array<std::vector<double>, 3>>(
        static_cast<int>(Resource::COUNT_SENTINEL), std::array<std::vector<double>, 3>{});
};
} // namespace DI