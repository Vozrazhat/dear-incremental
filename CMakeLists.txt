cmake_minimum_required(VERSION 4.0)
Project (dear-incremental)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Install spdlog my beloved
include(FetchContent)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

# Add in the imgui
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui/backends")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui/misc/cpp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include")
file(GLOB DEP_IMGUI_LIST "${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui/*.cpp")
file(GLOB DEP_GLAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/*.c")
file(GLOB VIEW_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/view/*.cpp")
file(GLOB MODEL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/model/*.cpp")
file(GLOB VIEWMODEL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodel/*.cpp")
set(DEP_IMGUI_BACKENDS "${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui/backends/imgui_impl_glfw.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui/backends/imgui_impl_opengl3.cpp")

add_executable(dear-incremental
    src/main.cpp
    ${VIEW_SOURCES}
    ${MODEL_SOURCES}
    ${VIEWMODEL_SOURCES}
    ${DEP_IMGUI_LIST}
    ${DEP_IMGUI_BACKENDS}
    ${DEP_GLAD_LIST}
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui/misc/cpp/imgui_stdlib.cpp
)

target_compile_definitions(dear-incremental PRIVATE
    SPDLOG_ACTIVE_LEVEL=$<IF:$<CONFIG:Debug>,SPDLOG_LEVEL_DEBUG,SPDLOG_LEVEL_INFO>
)

target_link_libraries(dear-incremental PRIVATE spdlog::spdlog glfw nlohmann_json::nlohmann_json)
