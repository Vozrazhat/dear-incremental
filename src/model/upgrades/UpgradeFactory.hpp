#pragma once
#include "Upgrade.hpp"
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace DI {
using json = nlohmann::json;
class UpgradeFactory {
public:
    UpgradeFactory() = delete;

    // Upgrade, isDynamic is the bool
    static std::pair<Upgrade, bool> createUpgrade(json &j, ResourceManager &rm);
    static std::vector<std::pair<Upgrade, bool>> createAllUpgrades(json &&j, ResourceManager &rm);
    static std::vector<std::pair<Upgrade, bool>> createAllUpgrades(ResourceManager &rm) {
        return createAllUpgrades(json::parse(std::ifstream("./src/model/upgrades/Upgrades.json")),
                                 rm);
    };

private:
    static CurveParams getParams(json &j);
};

} // namespace DI
