#include "ResourceManager.hpp"

#include <cmath>
#include <numeric>

namespace DI {
ResourceManager::ResourceManager() {
    for (auto &arr : resource_vps_) {
        for (auto &vec : arr) {
            // Total meme for now. This is the max number of upgrades. Maybe make a global define or something.
            vec.reserve(256);
        }
    }
}

double &ResourceManager::requestSlot(Resource r, SlotType t) {
    auto &resource_slot = resource_vps_.at(r).at(t);
    resource_slot.push_back(0);
    return resource_slot.at(resource_slot.size() - 1);
}
void ResourceManager::process(float delta) {
    for (int i{}; i < resource_values_.size(); ++i) {
        auto &base_vals = resource_vps_[i][0];
        auto &mult_vals = resource_vps_[i][1];
        auto &exp_vals = resource_vps_[i][2];
        resource_values_[i] +=
            delta * std::pow(std::reduce(base_vals.begin(), base_vals.end()) *
                                 std::accumulate(mult_vals.begin(), mult_vals.end(), 1.0, std::multiplies<double>()),
                             std::accumulate(exp_vals.begin(), exp_vals.end(), 1.0, std::multiplies<double>()));
    }
}
} // namespace DI