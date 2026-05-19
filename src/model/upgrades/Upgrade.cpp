#include "Upgrade.hpp"
// #include <cmath>
#include <cassert>

namespace DI {
Upgrade::Upgrade(std::string id, std::string name, int limit)
    : id_(id), name_(name), limit_(limit) {}

void Upgrade::buy() {
    if (canBuy()) {
        ++amount_;
        refreshCost();
        refreshImpact();
    }
}
bool Upgrade::canBuy() const {
    return (!limit_ || (amount_ < limit_)) &&
           std::all_of(cost_functions_.begin(), cost_functions_.end(),
                       [](const RefboundCurve &rc) { return rc.value <= rc.cache; });
}
void Upgrade::refreshCost() {
    for (int i{}; i < cost_functions_.size(); ++i) {
        RefboundCurve &f = cost_functions_[i];
        f.runFunction();
        // We are assuming that cost functions have the same length as cost resources
        cost_resources_[i].count = f.cache;
    }
}
void Upgrade::refreshImpact() {
    for (RefboundCurve &f : impact_functions_) {
        f.value.get() = f.runFunction();
    }
}
void Upgrade::addCost(Resource r, RefboundCurve &rc) {
    rc.runFunction();
    cost_functions_.push_back(std::move(rc));
    cost_resources_.emplace_back(r, rc.cache);
}
void Upgrade::addImpact(ResourceSlot rs, RefboundCurve &rc) {
    rc.runFunction();
    impact_functions_.push_back(std::move(rc));
    impact_resources_.push_back(rs);
}
} // namespace DI