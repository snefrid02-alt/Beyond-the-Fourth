/*
 * This is free and unencumbered software released into the public domain.
 * For more information, please refer to <http://unlicense.org/>
 */

#pragma once

#include "../engine/Player5D.hpp"
#include "../engine/Physics5D.hpp"
#include "../engine/Renderer.hpp"
#include "../core/DimensionState.hpp"
#include "Level.hpp"
#include "AdvancedLevels.hpp"
#include "AdvancedLevels2.hpp"
#include "BossLevel.hpp"
#include <memory>
#include <vector>
#include <fstream>

/**
 * SaveData - Persistent game progress
 */
struct SaveData {
    int currentLevel;
    int highestLevelReached;
    float totalPlayTime;

    SaveData() : currentLevel(0), highestLevelReached(0), totalPlayTime(0.0f) {}

    bool save(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) return false;
        
        file.write(reinterpret_cast<const char*>(&currentLevel), sizeof(currentLevel));
        file.write(reinterpret_cast<const char*>(&highestLevelReached), sizeof(highestLevelReached));
        file.write(reinterpret_cast<const char*>(&totalPlayTime), sizeof(totalPlayTime));
        
        return true;
    }

    bool load(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) return false;
        
        file.read(reinterpret_cast<char*>(&currentLevel), sizeof(currentLevel));
        file.read(reinterpret_cast<char*>(&highestLevelReached), sizeof(highestLevelReached));
        file.read(reinterpret_cast<char*>(&totalPlayTime), sizeof(totalPlayTime));
        
        return true;
    }
};

/**
 * Game - Main game logic and state management
 */
class Game {
public:
    Player5D player;
    DimensionState dimState;
    Renderer renderer;
    SaveData saveData;
    
    std::vector<std::unique_ptr<Level>> levels;
    Level* currentLevel;
    int currentLevelIndex;
    
    bool levelComplete;
    float levelCompleteTimer;
    
    // Input state
    bool keys[1024];
    glm::vec2 mousePos;
    bool mouseLocked;

    Game() 
        : currentLevel(nullptr)
        , currentLevelIndex(0)
        , levelComplete(false)
        , levelCompleteTimer(0.0f)
        , mouseLocked(false)
    {
        for (int i = 0; i < 1024; ++i) keys[i] = false;
        
        // Initialize levels - 11 total levels now!
        levels.push_back(std::make_unique<Level1>());
        levels.push_back(std::make_unique<Level2>());
        levels.push_back(std::make_unique<Level3>());
        levels.push_back(std::make_unique<Level4_PentacubeMaze>());
        levels.push_back(std::make_unique<Level5_DimensionalBridges>());
        levels.push_back(std::make_unique<Level6_HyperspaceTeleportation>());
        levels.push_back(std::make_unique<Level7_PhaseObjects>());
        levels.push_back(std::make_unique<Level8_RotationPuzzles>());
        levels.push_back(std::make_unique<Level9_TemporalEchoes>());
        levels.push_back(std::make_unique<Level10_HypersurfaceWalking>());
        levels.push_back(std::make_unique<Level11_ThePentarch>());  // Boss level!
        
        player.setDimensionState(&dimState);
    }

    bool initialize() {
        if (!renderer.initialize()) {
            return false;
        }

        // Load save data
        saveData.load("savegame.dat");
        
        // Start at first level or saved level
        loadLevel(saveData.currentLevel);
        
        return true;
    }

    void loadLevel(int levelIndex) {
        if (levelIndex < 0 || levelIndex >= static_cast<int>(levels.size())) {
            levelIndex = 0;
        }

        currentLevelIndex = levelIndex;
        currentLevel = levels[levelIndex].get();
        currentLevel->initialize();
        
        // Reset player
        player.position = currentLevel->playerStartPos;
        player.velocity = Vec5D();
        player.isGrounded = false;
        
        // Reset dimension state
        dimState = DimensionState();
        
        levelComplete = false;
        levelCompleteTimer = 0.0f;
    }

    void update(float deltaTime) {
        // Update save data
        saveData.totalPlayTime += deltaTime;

        // Handle input
        handleInput(deltaTime);
        
        // Update dimension state
        dimState.update(deltaTime);
        
        // Update level objects
        if (currentLevel) {
            currentLevel->update(deltaTime);
            
            // Update physics
            Physics5D::updatePlayer(player, currentLevel->objects, deltaTime);
            
            // Check level completion
            if (currentLevel->isComplete(player) && !levelComplete) {
                levelComplete = true;
                levelCompleteTimer = 2.0f;  // Wait 2 seconds before advancing
                
                // Update save data
                if (currentLevelIndex >= saveData.highestLevelReached) {
                    saveData.highestLevelReached = currentLevelIndex + 1;
                }
                saveData.currentLevel = currentLevelIndex + 1;
                saveData.save("savegame.dat");
            }
        }
        
        // Handle level transition
        if (levelComplete) {
            levelCompleteTimer -= deltaTime;
            if (levelCompleteTimer <= 0.0f) {
                nextLevel();
            }
        }
    }

    void render(int screenWidth, int screenHeight) {
        if (!currentLevel) return;
        
        // Build object list including player
        std::vector<std::shared_ptr<GameObject5D>> renderList;
        
        // Add all level objects
        for (auto& obj : currentLevel->objects) {
            renderList.push_back(obj);
        }
        
        // Add player (wrapped in shared_ptr for rendering only)
        auto playerPtr = std::shared_ptr<GameObject5D>(&player, [](GameObject5D*){});
        renderList.push_back(playerPtr);
        
        // Render scene
        renderer.renderScene(renderList, dimState, screenWidth, screenHeight);
    }

    void nextLevel() {
        int nextIndex = currentLevelIndex + 1;
        if (nextIndex < static_cast<int>(levels.size())) {
            loadLevel(nextIndex);
        } else {
            // Game complete! Loop back to first level
            loadLevel(0);
        }
    }

    void previousLevel() {
        int prevIndex = currentLevelIndex - 1;
        if (prevIndex >= 0) {
            loadLevel(prevIndex);
        }
    }

    void restartLevel() {
        loadLevel(currentLevelIndex);
    }

    void handleInput(float deltaTime) {
        // Movement input (WASD)
        glm::vec3 moveInput(0.0f);
        
        if (keys['w'] || keys['W']) moveInput.z -= 1.0f;
        if (keys['s'] || keys['S']) moveInput.z += 1.0f;
        if (keys['a'] || keys['A']) moveInput.x -= 1.0f;
        if (keys['d'] || keys['D']) moveInput.x += 1.0f;
        
        // Normalize diagonal movement
        if (glm::length(moveInput) > 0.1f) {
            moveInput = glm::normalize(moveInput);
        }
        
        player.setMoveInput(moveInput);
        
        // Dimension rotation (Q/E for different planes)
        if (keys['q'] || keys['Q']) {
            // Rotate XY -> XW
            dimState.rotateToDimensions(0, 1, 3);  // Show X, Y, W
        }
        if (keys['e'] || keys['E']) {
            // Rotate XY -> XV
            dimState.rotateToDimensions(0, 1, 4);  // Show X, Y, V
        }
        if (keys['r'] || keys['R']) {
            // Return to XYZ
            dimState.rotateToDimensions(0, 1, 2);  // Show X, Y, Z
        }
        
        // Number keys for direct dimension selection
        if (keys['1']) dimState.rotateToDimensions(0, 1, 2);  // XYZ
        if (keys['2']) dimState.rotateToDimensions(0, 1, 3);  // XYW
        if (keys['3']) dimState.rotateToDimensions(0, 1, 4);  // XYV
        if (keys['4']) dimState.rotateToDimensions(0, 2, 3);  // XZW
        if (keys['5']) dimState.rotateToDimensions(0, 2, 4);  // XZV
        if (keys['6']) dimState.rotateToDimensions(1, 2, 3);  // YZW
        if (keys['7']) dimState.rotateToDimensions(1, 2, 4);  // YZV
        if (keys['8']) dimState.rotateToDimensions(0, 3, 4);  // XWV
        if (keys['9']) dimState.rotateToDimensions(1, 3, 4);  // YWV
        if (keys['0']) dimState.rotateToDimensions(2, 3, 4);  // ZWV
    }

    void handleKeyPress(int key) {
        if (key >= 0 && key < 1024) {
            keys[key] = true;
        }
        
        // Space for jump
        if (key == ' ') {
            player.setJumpPressed();
        }
        
        // Left Shift for dash
        if (key == 340) {  // GLFW_KEY_LEFT_SHIFT
            player.setDashPressed();
        }
        
        // ESC for restart
        if (key == 256) {  // GLFW_KEY_ESCAPE
            restartLevel();
        }
        
        // F1/F2 for level navigation
        if (key == 290) {  // F1
            previousLevel();
        }
        if (key == 291) {  // F2
            nextLevel();
        }
    }

    void handleKeyRelease(int key) {
        if (key >= 0 && key < 1024) {
            keys[key] = false;
        }
    }

    std::string getCurrentViewName() const {
        return dimState.getCurrentViewName();
    }

    std::string getCurrentLevelName() const {
        return currentLevel ? currentLevel->name : "No Level";
    }

    std::string getCurrentLevelDescription() const {
        return currentLevel ? currentLevel->description : "";
    }
};
