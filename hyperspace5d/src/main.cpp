#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include "game/Game.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "HyperSpace5D - 5D Puzzle Platformer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(glewError) << std::endl;
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Enable VSync
    SDL_GL_SetSwapInterval(1);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 450");

    // Initialize game
    Game game;
    if (!game.initialize()) {
        std::cerr << "Failed to initialize game" << std::endl;
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::cout << "=== HyperSpace5D - 5D Puzzle Platformer ===" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  WASD - Move" << std::endl;
    std::cout << "  Space - Jump" << std::endl;
    std::cout << "  Shift - Dash" << std::endl;
    std::cout << "  Q/E/R - Rotate dimensions" << std::endl;
    std::cout << "  1-0 - Direct dimension views" << std::endl;
    std::cout << "  F1/F2 - Previous/Next level" << std::endl;
    std::cout << "  ESC - Restart level" << std::endl;
    std::cout << "===========================================" << std::endl;

    // Game loop
    bool running = true;
    Uint32 lastTime = SDL_GetTicks();
    bool showDebugUI = true;
    bool showHelp = true;

    while (running) {
        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // Cap delta time to prevent physics issues
        if (deltaTime > 0.1f) deltaTime = 0.1f;

        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_F3) {
                    showDebugUI = !showDebugUI;
                }
                else if (event.key.keysym.sym == SDLK_F4) {
                    showHelp = !showHelp;
                }
                else {
                    game.handleKeyPress(event.key.keysym.sym);
                }
            }
            else if (event.type == SDL_KEYUP) {
                game.handleKeyRelease(event.key.keysym.sym);
            }
        }

        // Update game
        game.update(deltaTime);

        // Render game
        game.render(SCREEN_WIDTH, SCREEN_HEIGHT);

        // Render ImGui UI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Help window
        if (showHelp) {
            ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(400, 250), ImGuiCond_FirstUseEver);
            ImGui::Begin("Controls & Info", &showHelp);
            
            ImGui::TextColored(ImVec4(0.3f, 0.8f, 1.0f, 1.0f), "HyperSpace5D - 5D Puzzle Platformer");
            ImGui::Separator();
            
            ImGui::Text("Movement:");
            ImGui::BulletText("WASD - Move in current 3D slice");
            ImGui::BulletText("Space - Jump");
            ImGui::BulletText("Shift - Dash");
            
            ImGui::Spacing();
            ImGui::Text("Dimension Control:");
            ImGui::BulletText("Q/E/R - Quick dimension rotation");
            ImGui::BulletText("1-0 - Direct dimension views");
            ImGui::BulletText("  1: XYZ   2: XYW   3: XYV");
            ImGui::BulletText("  4: XZW   5: XZV   6: YZW");
            ImGui::BulletText("  7: YZV   8: XWV   9: YWV   0: ZWV");
            
            ImGui::Spacing();
            ImGui::Text("Other:");
            ImGui::BulletText("ESC - Restart level");
            ImGui::BulletText("F1/F2 - Previous/Next level");
            ImGui::BulletText("F3 - Toggle debug UI");
            ImGui::BulletText("F4 - Toggle this help");
            
            ImGui::End();
        }

        // Debug UI
        if (showDebugUI) {
            ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH - 310, 10), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
            ImGui::Begin("Debug Info", &showDebugUI);
            
            ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.3f, 1.0f), "%s", game.getCurrentViewName().c_str());
            ImGui::Separator();
            
            ImGui::Text("Level: %s", game.getCurrentLevelName().c_str());
            ImGui::TextWrapped("%s", game.getCurrentLevelDescription().c_str());
            
            ImGui::Separator();
            ImGui::Text("Player Position:");
            ImGui::Text("  X: %.2f", game.player.position.x);
            ImGui::Text("  Y: %.2f", game.player.position.y);
            ImGui::Text("  Z: %.2f", game.player.position.z);
            ImGui::Text("  W: %.2f", game.player.position.w);
            ImGui::Text("  V: %.2f", game.player.position.v);
            
            ImGui::Separator();
            ImGui::Text("Player Velocity:");
            ImGui::Text("  X: %.2f", game.player.velocity.x);
            ImGui::Text("  Y: %.2f", game.player.velocity.y);
            ImGui::Text("  Z: %.2f", game.player.velocity.z);
            ImGui::Text("  W: %.2f", game.player.velocity.w);
            ImGui::Text("  V: %.2f", game.player.velocity.v);
            
            ImGui::Separator();
            ImGui::Text("State:");
            ImGui::Text("  Grounded: %s", game.player.isGrounded ? "Yes" : "No");
            ImGui::Text("  On Wall: %s", game.player.isOnWall ? "Yes" : "No");
            ImGui::Text("  Dashing: %s", game.player.isDashing ? "Yes" : "No");
            ImGui::Text("  Can Dash: %s", game.player.canDash ? "Yes" : "No");
            
            ImGui::Separator();
            ImGui::Text("Dimension Transition:");
            ImGui::ProgressBar(game.dimState.transitionProgress);
            
            ImGui::Separator();
            ImGui::Text("Performance:");
            ImGui::Text("  FPS: %.1f", io.Framerate);
            ImGui::Text("  Frame Time: %.3f ms", 1000.0f / io.Framerate);
            
            ImGui::End();
        }

        // Main menu overlay
        if (game.levelComplete) {
            ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 50));
            ImGui::SetNextWindowSize(ImVec2(300, 100));
            ImGui::Begin("Level Complete!", nullptr, 
                ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            
            ImGui::TextColored(ImVec4(0.3f, 1.0f, 0.3f, 1.0f), "Level Complete!");
            ImGui::Text("Loading next level...");
            ImGui::ProgressBar(1.0f - (game.levelCompleteTimer / 2.0f));
            
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
