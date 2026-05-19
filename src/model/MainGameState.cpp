#include "MainGameState.hpp"
#include <spdlog/spdlog.h>

namespace DI {
MainGameState::MainGameState() {

    // DEBUG
    CurveRegistry reg{};

    // debugUpgrade = Upgrade("test", "testname", 0);

    CurveParams icp = {debugUpgrade.amount(), 0.0, 1.0, 0.0};
    CurveFunction icf = reg.generateCurve("linear", icp);
    ResourceSlot irs = {Resource::NEURONS, SlotType::BASE};
    double &islot = resource_manager_.requestSlot(irs);
    RefboundCurve irc = {islot, icf};
    debugUpgrade.addImpact(irs, irc);

    CurveParams icp2 = {debugUpgradeMult.amount(), 1.0, 1.0, 0.0};
    CurveFunction icf2 = reg.generateCurve("linear", icp2);
    ResourceSlot irs2 = {Resource::NEURONS, SlotType::MULT};
    double &islot2 = resource_manager_.requestSlot(irs2);
    RefboundCurve irc2 = {islot2, icf2};
    debugUpgradeMult.addImpact(irs2, irc2);

    CurveParams icp3 = {debugUpgradeExp.amount(), 1.0, 1.0, 0.0};
    CurveFunction icf3 = reg.generateCurve("linear", icp3);
    ResourceSlot irs3 = {Resource::NEURONS, SlotType::EXP};
    double &islot3 = resource_manager_.requestSlot(irs3);
    RefboundCurve irc3 = {islot3, icf3};
    debugUpgradeExp.addImpact(irs3, irc3);
}

void MainGameState::process(float delta) { resource_manager_.process(delta); }

} // namespace DI