#pragma once
#include "CurveRegistry.hpp"
#include "ResourceManager.hpp"
#include <string>
#include <vector>

namespace DI {
class Upgrade {
public:
    Upgrade(ResourceManager &man, std::string name) : rm_(man), name_(name) {
        reg();
        refresh();
    }
    virtual ~Upgrade() = default;

    virtual std::string name() { return name_; }
    virtual std::pair<Resource, double> cost() { return cost_; }
    virtual void buy() {
        if (canBuy()) {
            ++amount_;
            refresh();
        }
    };
    virtual bool canBuy() { return amount_ < limit_ && rm_.getResourceRef(cost().first) >= cost().second; }
    virtual int limit() { return limit_; }

    // Refreshes the impacted values and cost.
    virtual void refresh() = 0;
    // sets impacted values.
    virtual void reg() = 0;

protected:
    // std::string id_{};
    int limit_{};
    int amount_{};
    std::pair<Resource, double> cost_{};
    std::string name_{};
    ResourceManager &rm_;

    CurveFunction cost_function_{};
    CurveFunction impact_function_{};
    // std::vector<double &> impacted_values_{};
};

} // namespace DI