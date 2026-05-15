#include "MainGameState.hpp"
#include <spdlog/spdlog.h>

namespace DI {

void MainGameState::process(float delta) { resource_manager_.process(delta); }

} // namespace DI