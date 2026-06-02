#include "UpgradeFactory.hpp"
#include "CurveRegistry.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

namespace DI {
using json = nlohmann::json;
std::pair<Upgrade, bool> UpgradeFactory::createUpgrade(json &j, ResourceManager &rm) {

    // Not type checking anything lol
    Upgrade upgrade{j["id"], j["name"], j["limit"]};

    // CurveParams icp = {upgrade.amount(), 0.0, 1.0, 0.0};
    CurveParams icp = parseParams(j["impact_function_params"]);
    CurveFunction icf = CurveRegistry::generate(j["impact_function"], icp);

    // put this into a helper
    ResourceSlot irs = {Resource::NEURONS, SlotType::BASE};
    double &islot = rm.requestSlot(irs);
    RefboundCurve irc = {islot, icf};
    upgrade.addImpact(irs, irc);

    // return std::pair<Upgrade, bool>{{"null", "null", 0}, false};
}

std::vector<std::pair<Upgrade, bool>>

UpgradeFactory::createAllUpgrades(json &&j, ResourceManager &rm) {

    std::vector<std::pair<Upgrade, bool>> allUpgrades{};
    for (auto &[key, huh] : j.items()) {
        // SPDLOG_DEBUG("{}", huh["name"]);
        allUpgrades.emplace_back(createUpgrade(huh, rm));
    }
    return allUpgrades;
}

CurveParams UpgradeFactory::parseParams(json &j) {
    // TODO
    return CurveParams();
}

ResourceSlot UpgradeFactory::parseResourceSlot(json &j) {
    // TODO
    return ResourceSlot();
}

} // namespace DI
