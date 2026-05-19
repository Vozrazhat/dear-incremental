#pragma once
#include <algorithm>

#include "ResourceManager.hpp"
// Debug
#include "upgrades/CurveRegistry.hpp"
#include "upgrades/Upgrade.hpp"

namespace DI {
class MainGameState {
public:
    MainGameState();
    ~MainGameState() = default;

    double getValue(Resource r) { return resource_manager_.getResourceRef(r); };
    // Pass "delta" seconds.
    void process(float delta);

    // DEBUG
    void buyDebugUpgrade() { debugUpgrade.buy(); }
    void buyDebugUpgradeMult() { debugUpgradeMult.buy(); }
    void buyDebugUpgradeExp() { debugUpgradeExp.buy(); }

    Upgrade debugUpgrade{"test", "testname", 0};
    Upgrade debugUpgradeMult{"testm", "testnamem", 0};
    Upgrade debugUpgradeExp{"teste", "testnamee", 0};

    // This is REALLLY for debug
    ResourceManager &getResourceManager() { return resource_manager_; }

private:
    ResourceManager resource_manager_{};
    double tickspeed_{1.0};
};
} // namespace DI
