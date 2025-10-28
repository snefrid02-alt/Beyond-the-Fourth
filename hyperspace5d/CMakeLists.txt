cmake_minimum_required(VERSION 3.15)
project(HyperSpace5D VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

# ImGui sources (assuming system-wide installation or local copy)
set(IMGUI_DIR /usr/include/imgui)
if(EXISTS ${IMGUI_DIR})
    set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    )
    include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)
else()
    message(WARNING "ImGui not found at ${IMGUI_DIR}, you may need to adjust the path")
endif()

# Source files
set(SOURCES
    src/main.cpp
)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${SDL2_LIBRARIES}
    GL
    GLU
    SDL2
    GLEW
    pthread
    dl
)

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)

# Copy shaders to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy assets to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY shaders DESTINATION share/${PROJECT_NAME})
install(DIRECTORY assets DESTINATION share/${PROJECT_NAME})

# Print configuration
message(STATUS "")
message(STATUS "=== HyperSpace5D Configuration ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "==================================")
message(STATUS "")
