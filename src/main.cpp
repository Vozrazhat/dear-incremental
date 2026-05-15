#include "model/MainGameState.hpp"
#include "view/MainGameWindow.hpp"
#include "viewmodel/MainGameViewModel.hpp"
#include <chrono>
#include <spdlog/spdlog.h>
#include <thread>

int main() {
#ifdef NDEBUG
    spdlog::set_level(spdlog::level::info);
#else
    spdlog::set_level(spdlog::level::debug);
#endif
    SPDLOG_INFO("Compiling at least.");
    SPDLOG_DEBUG("Running in debug mode");

    DI::MainGameState main_game_state;
    DI::MainGameViewModel main_game_view_model(main_game_state);
    DI::MainGameWindow main_game_window(main_game_view_model);

    // Spawn our physics processing thread
    bool game_running = true;
    std::thread physics_thread([&]() {
        auto current_time = std::chrono::high_resolution_clock::now();
        while (game_running) {
            auto new_time = std::chrono::high_resolution_clock::now();
            double frame_time = std::chrono::duration<double>(new_time - current_time).count();
            current_time = new_time;
            main_game_state.process(frame_time);
        }
    });

    main_game_window.run();
    game_running = false;
    if (physics_thread.joinable()) {
        physics_thread.join();
    }

    return 0;
}