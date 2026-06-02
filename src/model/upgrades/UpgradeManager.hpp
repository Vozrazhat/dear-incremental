#pragma once
#include "../ResourceManager.hpp"
#include "Upgrade.hpp"
#include "UpgradeFactory.hpp"
#include <map>
#include <string>
#include <vector>

namespace DI {
struct UpgradeInfo {
    std::string id;
    bool dynamic;
    int index;
    bool visible = false;
    std::vector<std::string> dependencies{};
};

// Dynamic upgrades depend on a resource value that changes every frame and so need to be updated.
// Static upgrades only depend on their own amounts and so can be updated on purchase only.

class UpgradeManager {
public:
    UpgradeManager(ResourceManager &rm);
    ~UpgradeManager() = default;

    Upgrade &getUpgrade(const std::string &id) { return getUpgrade(upgrade_db_.at(id)); }
    Upgrade &getUpgrade(const UpgradeInfo &info) {
        return (info.dynamic ? dynamic_upgrades_ : static_upgrades_)[info.index];
    }

private:
    std::map<std::string, UpgradeInfo> upgrade_db_;
    std::vector<Upgrade> dynamic_upgrades_;
    std::vector<Upgrade> static_upgrades_;
};

} // namespace DI
