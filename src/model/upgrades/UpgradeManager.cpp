#include "UpgradeManager.hpp"

namespace DI {
UpgradeManager::UpgradeManager(ResourceManager &rm) { UpgradeFactory::createAllUpgrades(rm); }
} // namespace DI