/*
 * This is free and unencumbered software released into the public domain.
 * For more information, please refer to <http://unlicense.org/>
 */

#pragma once

#include "Level.hpp"
#include <cmath>

/**
 * Level 8: 5D Rotation Puzzles
 * 
 * Teaches: Sequential dimensional rotations, combination locks
 * 
 * Puzzle: Keys/switches require specific dimensional rotation sequences
 * to activate. Like combination locks in 5D space.
 * 
 * Skills: Sequence memory, precise dimensional control, puzzle solving
 */
class Level8_RotationPuzzles : public Level {
public:
    Level8_RotationPuzzles() : Level("Rotation Locks", 8) {
        description = "Unlock passages with the correct dimensional rotation sequences!";
    }

    void initialize() override {
        objects.clear();
        
        // Ground
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, 0, 0, 0, 0),
            Vec5D(80, 1, 50, 50, 50)
        );
        addObject(ground);
        
        // Start
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        addObject(start);
        
        // Puzzle 1: Lock visible in XYZ, key visible in XYW
        // Lock (obstacle)
        auto lock1 = std::make_shared<Platform5D>(
            Vec5D(10, 2, 0, 0, 0),
            Vec5D(2, 4, 8, 0.5f, 8)
        );
        lock1->color = glm::vec3(0.8f, 0.2f, 0.2f);
        addObject(lock1);
        
        // Key platform (only accessible from W dimension)
        auto key1 = std::make_shared<Platform5D>(
            Vec5D(8, 2, 0, 5, 0),
            Vec5D(2, 0.5f, 2, 2, 2)
        );
        key1->color = glm::vec3(1.0f, 0.8f, 0.2f);
        addObject(key1);
        
        // Puzzle 2: Requires viewing XYV then XWV in sequence
        auto lock2 = std::make_shared<Platform5D>(
            Vec5D(20, 2, 0, 0, 0),
            Vec5D(2, 4, 0.5f, 8, 8)
        );
        lock2->color = glm::vec3(0.8f, 0.2f, 0.2f);
        addObject(lock2);
        
        auto key2A = std::make_shared<Platform5D>(
            Vec5D(18, 2, 0, 0, 6),
            Vec5D(2, 0.5f, 2, 2, 2)
        );
        key2A->color = glm::vec3(1.0f, 0.8f, 0.2f);
        addObject(key2A);
        
        auto key2B = std::make_shared<Platform5D>(
            Vec5D(22, 2, 0, 6, 6),
            Vec5D(2, 0.5f, 2, 2, 2)
        );
        key2B->color = glm::vec3(1.0f, 0.8f, 0.2f);
        addObject(key2B);
        
        // Puzzle 3: Complex three-way lock
        auto lock3A = std::make_shared<Platform5D>(
            Vec5D(30, 2, 3, 0, 0),
            Vec5D(2, 4, 2, 0.5f, 8)
        );
        lock3A->color = glm::vec3(0.8f, 0.2f, 0.2f);
        addObject(lock3A);
        
        auto lock3B = std::make_shared<Platform5D>(
            Vec5D(30, 2, -3, 0, 0),
            Vec5D(2, 4, 2, 8, 0.5f)
        );
        lock3B->color = glm::vec3(0.8f, 0.2f, 0.2f);
        addObject(lock3B);
        
        // Keys for puzzle 3
        auto key3A = std::make_shared<Platform5D>(
            Vec5D(28, 3, 0, 7, 0),
            Vec5D(1.5f, 0.5f, 1.5f, 1.5f, 1.5f)
        );
        key3A->color = glm::vec3(1.0f, 0.8f, 0.2f);
        addObject(key3A);
        
        auto key3B = std::make_shared<Platform5D>(
            Vec5D(32, 3, 0, 0, 7),
            Vec5D(1.5f, 0.5f, 1.5f, 1.5f, 1.5f)
        );
        key3B->color = glm::vec3(1.0f, 0.8f, 0.2f);
        addObject(key3B);
        
        auto key3C = std::make_shared<Platform5D>(
            Vec5D(30, 3, 0, 7, 7),
            Vec5D(1.5f, 0.5f, 1.5f, 1.5f, 1.5f)
        );
        key3C->color = glm::vec3(1.0f, 0.8f, 0.2f);
        addObject(key3C);
        
        // Path platforms
        addPlatform(Vec5D(5, 2, 0, 2, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.7f, 0.7f, 0.7f));
        addPlatform(Vec5D(15, 2, 0, 0, 0), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.7f, 0.7f, 0.7f));
        addPlatform(Vec5D(25, 2, 0, 3, 3), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.7f, 0.7f, 0.7f));
        addPlatform(Vec5D(35, 2, 0, 0, 0), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.7f, 0.7f, 0.7f));
        
        // Goal
        auto goalPlatform = std::make_shared<Platform5D>(
            Vec5D(45, 1, 0, 0, 0),
            Vec5D(5, 0.5f, 5, 5, 5)
        );
        addObject(goalPlatform);
        
        auto goal = std::make_shared<Goal5D>(Vec5D(45, 3, 0, 0, 0));
        addObject(goal);
        
        playerStartPos = Vec5D(0, 3, 0, 0, 0);
    }

private:
    void addPlatform(const Vec5D& pos, const Vec5D& size, const glm::vec3& color) {
        auto platform = std::make_shared<Platform5D>(pos, size);
        platform->color = color;
        addObject(platform);
    }
};

/**
 * Level 9: Temporal Echoes
 * 
 * Teaches: V-dimension as pseudo-temporal, trail usage
 * 
 * Puzzle: Objects leave "trails" in the V-dimension that persist and can
 * be used as platforms. Think of V as a time-like dimension where your
 * past positions remain accessible.
 * 
 * Skills: Creative use of 5th dimension, trail planning, self-assistance
 */
class Level9_TemporalEchoes : public Level {
public:
    Level9_TemporalEchoes() : Level("Temporal Echoes", 9) {
        description = "Your echoes in the V-dimension persist. Use them as stepping stones!";
    }

    void initialize() override {
        objects.clear();
        
        // Ground
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, 0, 0, 0, 0),
            Vec5D(90, 1, 40, 40, 80)
        );
        addObject(ground);
        
        // Start
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        addObject(start);
        
        // Echo trails (simulated as platforms at different V coordinates)
        // In a full implementation, these would be dynamically created
        
        // Trail generator platforms - standing here creates echoes
        auto echoGen1 = std::make_shared<Platform5D>(
            Vec5D(10, 2, 0, 0, 0),
            Vec5D(3, 0.5f, 3, 3, 15)
        );
        echoGen1->color = glm::vec3(0.6f, 0.8f, 1.0f);
        echoGen1->opacity = 0.6f;
        addObject(echoGen1);
        
        // Echo platforms at different V offsets
        for (int i = -3; i <= 3; ++i) {
            auto echo = std::make_shared<Platform5D>(
                Vec5D(15, 2, 0, 0, i * 5.0f),
                Vec5D(2, 0.5f, 2, 2, 1)
            );
            echo->color = glm::vec3(0.5f, 0.7f, 0.9f);
            echo->opacity = 0.5f + 0.1f * std::abs(i);
            addObject(echo);
        }
        
        // Second echo generator
        auto echoGen2 = std::make_shared<Platform5D>(
            Vec5D(25, 2, 0, 0, 0),
            Vec5D(3, 0.5f, 3, 3, 20)
        );
        echoGen2->color = glm::vec3(0.6f, 0.8f, 1.0f);
        echoGen2->opacity = 0.6f;
        addObject(echoGen2);
        
        // More echo platforms
        for (int i = -5; i <= 5; ++i) {
            auto echo = std::make_shared<Platform5D>(
                Vec5D(35, 3, 0, 0, i * 4.0f),
                Vec5D(2, 0.5f, 2, 2, 1)
            );
            echo->color = glm::vec3(0.5f, 0.7f, 0.9f);
            echo->opacity = 0.4f + 0.05f * std::abs(i);
            addObject(echo);
        }
        
        // Gap that requires echo platforms
        auto platformA = std::make_shared<Platform5D>(
            Vec5D(20, 2, 0, 0, -10),
            Vec5D(3, 0.5f, 3, 3, 3)
        );
        addObject(platformA);
        
        auto platformB = std::make_shared<Platform5D>(
            Vec5D(30, 3, 0, 0, 10),
            Vec5D(3, 0.5f, 3, 3, 3)
        );
        addObject(platformB);
        
        // V-dimension staircase
        for (int i = 0; i < 10; ++i) {
            auto step = std::make_shared<Platform5D>(
                Vec5D(45 + i * 2, 2 + i * 0.5f, 0, 0, i * 3.0f),
                Vec5D(2, 0.5f, 2, 2, 1)
            );
            step->color = glm::vec3(0.7f, 0.5f + i * 0.05f, 0.9f);
            addObject(step);
        }
        
        // Goal
        auto goalPlatform = std::make_shared<Platform5D>(
            Vec5D(70, 7, 0, 0, 27),
            Vec5D(5, 0.5f, 5, 5, 5)
        );
        addObject(goalPlatform);
        
        auto goal = std::make_shared<Goal5D>(Vec5D(70, 9, 0, 0, 27));
        addObject(goal);
        
        playerStartPos = Vec5D(0, 3, 0, 0, 0);
    }
};

/**
 * Level 10: Hypersurface Walking
 * 
 * Teaches: 4D hypersurface navigation, embedding understanding
 * 
 * Puzzle: Walk on 4D hypersurfaces embedded in 5D space. The surface
 * appears different from each 3D viewing angle, but it's all one
 * connected 4D structure.
 * 
 * Skills: Advanced topology, hypersurface intuition, embedding comprehension
 */
class Level10_HypersurfaceWalking : public Level {
public:
    Level10_HypersurfaceWalking() : Level("Hypersurface Path", 10) {
        description = "Walk the hypersurface. It's all connected in 4D, trust the geometry!";
    }

    void initialize() override {
        objects.clear();
        
        // Ground (minimal, hypersurface is main platform)
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, -5, 0, 0, 0),
            Vec5D(100, 1, 100, 100, 100)
        );
        addObject(ground);
        
        // Start
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        addObject(start);
        
        // Create a 4D "cylinder" in 5D space (3-sphere embedded in 5D)
        // This appears as different shapes from different views
        
        int numSegments = 24;
        float radius = 10.0f;
        float height = 40.0f;
        
        for (int i = 0; i < numSegments; ++i) {
            float theta = (i / (float)numSegments) * 2.0f * M_PI;
            float nextTheta = ((i + 1) / (float)numSegments) * 2.0f * M_PI;
            
            for (int j = 0; j < 20; ++j) {
                float t = j / 20.0f;
                
                // Parametric 4D surface in 5D space
                Vec5D pos(
                    t * height,                          // X: linear progression
                    2 + radius * std::cos(theta),        // Y: circular
                    radius * std::sin(theta),            // Z: circular
                    radius * std::cos(theta + t * M_PI), // W: twisted circular
                    radius * std::sin(theta + t * M_PI)  // V: twisted circular
                );
                
                auto segment = std::make_shared<Platform5D>(
                    pos,
                    Vec5D(2, 0.3f, 2, 2, 2)
                );
                
                // Color based on position
                float hue = theta / (2.0f * M_PI);
                segment->color = glm::vec3(
                    0.5f + 0.5f * std::cos(hue * 2.0f * M_PI),
                    0.5f + 0.5f * std::cos((hue + 0.33f) * 2.0f * M_PI),
                    0.5f + 0.5f * std::cos((hue + 0.67f) * 2.0f * M_PI)
                );
                
                addObject(segment);
            }
        }
        
        // Guide platforms
        addPlatform(Vec5D(5, 2, 0, 0, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.9f, 0.9f, 0.5f));
        addPlatform(Vec5D(15, 2, 0, 0, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.9f, 0.9f, 0.5f));
        addPlatform(Vec5D(25, 2, 0, 0, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.9f, 0.9f, 0.5f));
        addPlatform(Vec5D(35, 2, 0, 0, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.9f, 0.9f, 0.5f));
        
        // Goal
        auto goalPlatform = std::make_shared<Platform5D>(
            Vec5D(45, 1, 0, 0, 0),
            Vec5D(6, 0.5f, 6, 6, 6)
        );
        addObject(goalPlatform);
        
        auto goal = std::make_shared<Goal5D>(Vec5D(45, 3, 0, 0, 0));
        addObject(goal);
        
        playerStartPos = Vec5D(0, 3, 0, 0, 0);
    }

private:
    void addPlatform(const Vec5D& pos, const Vec5D& size, const glm::vec3& color) {
        auto platform = std::make_shared<Platform5D>(pos, size);
        platform->color = color;
        addObject(platform);
    }
};
