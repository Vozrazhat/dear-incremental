#pragma once
#include "CurveRegistry.hpp"
#include <algorithm>
#include <string>
#include <vector>

namespace DI {

struct RefboundCurve {
    std::reference_wrapper<double> value;
    CurveFunction function;
    // caches the most recent output of its function
    double cache{};

    double runFunction() {
        cache = function();
        return cache;
    };
};

class Upgrade {
public:
    Upgrade(std::string id, std::string name, int limit);
    ~Upgrade() = default;

    std::string name() { return name_; }

    void buy();
    bool canBuy() const;
    int limit() const { return limit_; }

    // Refreshes the impacted values and cost.
    void refreshCost();
    void refreshImpact();

    void addCost(Resource r, RefboundCurve &rc);
    void addImpact(ResourceSlot rs, RefboundCurve &rc);

    // info getting
    const std::vector<ResourceCount> costs() const { return cost_resources_; };
    const std::vector<ResourceSlot> impacts() const { return impact_resources_; };

    const int &amount() { return amount_; }

protected:
    std::string id_;
    std::string name_;

    const int limit_;
    int amount_{};

    // Actual stuff
    // The way to do this later is have the manager just keep one FAT vector of these
    // Then the individual upgrades just have indices into that
    // That would require up to know it's an updating one or not!
    std::vector<RefboundCurve> cost_functions_;
    std::vector<RefboundCurve> impact_functions_;

    // Stored only for info
    std::vector<ResourceCount> cost_resources_;
    std::vector<ResourceSlot> impact_resources_;
};
} // namespace DI