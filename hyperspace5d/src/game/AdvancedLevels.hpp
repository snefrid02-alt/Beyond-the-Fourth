/*
 * This is free and unencumbered software released into the public domain.
 * For more information, please refer to <http://unlicense.org/>
 */

#pragma once

#include "Level.hpp"
#include <cmath>

/**
 * Level 4: Pentacube Maze
 * 
 * Teaches: Complex 5D hypercube navigation, all dimensional views
 * 
 * Puzzle: Navigate a 5D hypercube where each 3D slice shows a different
 * section of a maze. The complete path requires viewing all 10 dimensional
 * perspectives to understand the full structure.
 * 
 * Skills: Spatial reasoning, comprehensive dimensional rotation, path planning
 */
class Level4_PentacubeMaze : public Level {
public:
    Level4_PentacubeMaze() : Level("Pentacube Maze", 4) {
        description = "The hypercube maze spans all 5 dimensions. Each view reveals different paths!";
    }

    void initialize() override {
        objects.clear();
        
        // Ground plane
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, 0, 0, 0, 0),
            Vec5D(50, 1, 50, 50, 50)
        );
        ground->color = glm::vec3(0.3f, 0.3f, 0.4f);
        addObject(ground);
        
        // Start platform
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        start->color = glm::vec3(0.7f, 0.7f, 0.8f);
        addObject(start);
        
        // Create hypercube maze structure
        // Central cube core
        addMazeSection(Vec5D(10, 2, 0, 0, 0), Vec5D(4, 3, 4, 4, 4), glm::vec3(0.6f, 0.4f, 0.4f));
        
        // XYZ dimension paths
        addMazeSection(Vec5D(15, 2, 0, 0, 0), Vec5D(2, 3, 4, 1, 1), glm::vec3(0.8f, 0.4f, 0.4f));
        addMazeSection(Vec5D(10, 2, 5, 0, 0), Vec5D(4, 3, 2, 1, 1), glm::vec3(0.8f, 0.4f, 0.4f));
        
        // W dimension passages (only visible in XYW, XZW, YZW views)
        addMazeSection(Vec5D(20, 2, 0, 5, 0), Vec5D(4, 3, 1, 4, 1), glm::vec3(0.4f, 0.8f, 0.4f));
        addMazeSection(Vec5D(10, 2, 0, 8, 0), Vec5D(2, 3, 1, 3, 1), glm::vec3(0.4f, 0.8f, 0.4f));
        
        // V dimension passages (only visible in XYV, XZV, YZV views)
        addMazeSection(Vec5D(25, 2, 0, 0, 6), Vec5D(4, 3, 1, 1, 4), glm::vec3(0.4f, 0.4f, 0.8f));
        addMazeSection(Vec5D(30, 2, 0, 0, 3), Vec5D(3, 3, 1, 1, 2), glm::vec3(0.4f, 0.4f, 0.8f));
        
        // WV dimension passages (only visible in XWV, YWV, ZWV views)
        addMazeSection(Vec5D(35, 2, 0, 4, 4), Vec5D(3, 3, 1, 3, 3), glm::vec3(0.8f, 0.4f, 0.8f));
        
        // Stepping stones through different dimensions
        addPlatform(Vec5D(17, 3, 2, 0, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.9f, 0.6f, 0.6f));
        addPlatform(Vec5D(22, 3, 0, 3, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.6f, 0.9f, 0.6f));
        addPlatform(Vec5D(27, 3, 0, 0, 4), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.6f, 0.6f, 0.9f));
        addPlatform(Vec5D(32, 3, 0, 2, 2), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.9f, 0.6f, 0.9f));
        
        // Goal platform at hypercube corner
        auto goalPlatform = std::make_shared<Platform5D>(
            Vec5D(40, 1, 0, 0, 0),
            Vec5D(5, 0.5f, 5, 5, 5)
        );
        goalPlatform->color = glm::vec3(0.9f, 0.9f, 0.9f);
        addObject(goalPlatform);
        
        // Goal
        auto goal = std::make_shared<Goal5D>(Vec5D(40, 3, 0, 0, 0));
        addObject(goal);
        
        playerStartPos = Vec5D(0, 3, 0, 0, 0);
    }

private:
    void addMazeSection(const Vec5D& pos, const Vec5D& size, const glm::vec3& color) {
        auto section = std::make_shared<Platform5D>(pos, size);
        section->color = color;
        addObject(section);
    }
    
    void addPlatform(const Vec5D& pos, const Vec5D& size, const glm::vec3& color) {
        auto platform = std::make_shared<Platform5D>(pos, size);
        platform->color = color;
        addObject(platform);
    }
};

/**
 * Level 5: Dimensional Bridges
 * 
 * Teaches: Mid-air dimension switching, timing, trust in invisible platforms
 * 
 * Puzzle: Bridges exist only in specific dimensional pairs. Player must
 * switch views while jumping to land on platforms that don't exist in
 * their starting view.
 * 
 * Skills: Reaction timing, dimensional awareness, multi-view mental mapping
 */
class Level5_DimensionalBridges : public Level {
public:
    Level5_DimensionalBridges() : Level("Dimensional Bridges", 5) {
        description = "Bridges appear and vanish as you rotate. Trust your other senses!";
    }

    void initialize() override {
        objects.clear();
        
        // Ground
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, 0, 0, 0, 0),
            Vec5D(60, 1, 30, 30, 30)
        );
        addObject(ground);
        
        // Start
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        addObject(start);
        
        // Bridge 1: Visible in XYZ, invisible in XYW
        auto bridge1 = std::make_shared<Platform5D>(
            Vec5D(8, 4, 0, 0, 0),
            Vec5D(8, 0.3f, 4, 0.5f, 4)
        );
        bridge1->color = glm::vec3(1.0f, 0.5f, 0.5f);
        addObject(bridge1);
        
        // Bridge 2: Visible in XYW, invisible in XYZ
        auto bridge2 = std::make_shared<Platform5D>(
            Vec5D(18, 4, 0, 0, 0),
            Vec5D(8, 0.3f, 0.5f, 4, 0.5f)
        );
        bridge2->color = glm::vec3(0.5f, 1.0f, 0.5f);
        addObject(bridge2);
        
        // Bridge 3: Visible in XYV, invisible in others
        auto bridge3 = std::make_shared<Platform5D>(
            Vec5D(28, 4, 0, 0, 0),
            Vec5D(8, 0.3f, 0.5f, 0.5f, 4)
        );
        bridge3->color = glm::vec3(0.5f, 0.5f, 1.0f);
        addObject(bridge3);
        
        // Bridge 4: Exists only in YZW view (perpendicular to X)
        auto bridge4 = std::make_shared<Platform5D>(
            Vec5D(38, 4, 0, 0, 0),
            Vec5D(0.5f, 0.3f, 8, 4, 0.5f)
        );
        bridge4->color = glm::vec3(1.0f, 1.0f, 0.5f);
        addObject(bridge4);
        
        // Safety platforms (visible in multiple views)
        addPlatform(Vec5D(12, 2, 0, 0, 0), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.7f, 0.7f, 0.7f));
        addPlatform(Vec5D(22, 2, 0, 0, 0), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.7f, 0.7f, 0.7f));
        addPlatform(Vec5D(32, 2, 0, 0, 0), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.7f, 0.7f, 0.7f));
        addPlatform(Vec5D(42, 2, 0, 0, 0), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.7f, 0.7f, 0.7f));
        
        // Goal
        auto goalPlatform = std::make_shared<Platform5D>(
            Vec5D(50, 1, 0, 0, 0),
            Vec5D(5, 0.5f, 5, 5, 5)
        );
        addObject(goalPlatform);
        
        auto goal = std::make_shared<Goal5D>(Vec5D(50, 3, 0, 0, 0));
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
 * Level 6: Hyperspace Teleportation
 * 
 * Teaches: Non-Euclidean thinking, 5D adjacency, portal mechanics
 * 
 * Puzzle: Portals connect distant points in 5D. What appears far in XYZ
 * might be adjacent when viewed in XWV. Understanding 5D topology is key.
 * 
 * Skills: Spatial topology, non-local connections, advanced dimensional reasoning
 */
class Level6_HyperspaceTeleportation : public Level {
public:
    Level6_HyperspaceTeleportation() : Level("Hyperspace Portals", 6) {
        description = "Space folds in on itself. What's far might be near in another view...";
    }

    void initialize() override {
        objects.clear();
        
        // Ground
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, 0, 0, 0, 0),
            Vec5D(80, 1, 80, 80, 80)
        );
        addObject(ground);
        
        // Start
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        addObject(start);
        
        // Portal pairs (represented as colored platforms in specific 5D locations)
        // Portal 1A (red) - entry at (10, 2, 0, 0, 0)
        auto portal1A = std::make_shared<Platform5D>(
            Vec5D(10, 2, 0, 0, 0),
            Vec5D(3, 0.3f, 3, 3, 3)
        );
        portal1A->color = glm::vec3(1.0f, 0.2f, 0.2f);
        portal1A->opacity = 0.7f;
        addObject(portal1A);
        
        // Portal 1B (red) - exit at (15, 2, 0, 15, 0) - far in W dimension
        auto portal1B = std::make_shared<Platform5D>(
            Vec5D(15, 2, 0, 15, 0),
            Vec5D(3, 0.3f, 3, 3, 3)
        );
        portal1B->color = glm::vec3(1.0f, 0.2f, 0.2f);
        portal1B->opacity = 0.7f;
        addObject(portal1B);
        
        // Portal 2A (blue) - entry
        auto portal2A = std::make_shared<Platform5D>(
            Vec5D(20, 2, 0, 15, 0),
            Vec5D(3, 0.3f, 3, 3, 3)
        );
        portal2A->color = glm::vec3(0.2f, 0.2f, 1.0f);
        portal2A->opacity = 0.7f;
        addObject(portal2A);
        
        // Portal 2B (blue) - exit at (25, 2, 0, 0, 20) - far in V dimension
        auto portal2B = std::make_shared<Platform5D>(
            Vec5D(25, 2, 0, 0, 20),
            Vec5D(3, 0.3f, 3, 3, 3)
        );
        portal2B->color = glm::vec3(0.2f, 0.2f, 1.0f);
        portal2B->opacity = 0.7f;
        addObject(portal2B);
        
        // Portal 3A (green) - entry
        auto portal3A = std::make_shared<Platform5D>(
            Vec5D(30, 2, 0, 0, 20),
            Vec5D(3, 0.3f, 3, 3, 3)
        );
        portal3A->color = glm::vec3(0.2f, 1.0f, 0.2f);
        portal3A->opacity = 0.7f;
        addObject(portal3A);
        
        // Portal 3B (green) - exit near goal
        auto portal3B = std::make_shared<Platform5D>(
            Vec5D(45, 2, 0, 0, 0),
            Vec5D(3, 0.3f, 3, 3, 3)
        );
        portal3B->color = glm::vec3(0.2f, 1.0f, 0.2f);
        portal3B->opacity = 0.7f;
        addObject(portal3B);
        
        // Connecting platforms
        addPlatform(Vec5D(12, 2, 0, 7, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.8f, 0.5f, 0.5f));
        addPlatform(Vec5D(17, 2, 0, 15, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.5f, 0.5f, 0.8f));
        addPlatform(Vec5D(22, 2, 0, 10, 10), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.5f, 0.8f, 0.5f));
        addPlatform(Vec5D(27, 2, 0, 0, 15), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.8f, 0.8f, 0.5f));
        
        // Goal
        auto goalPlatform = std::make_shared<Platform5D>(
            Vec5D(50, 1, 0, 0, 0),
            Vec5D(5, 0.5f, 5, 5, 5)
        );
        addObject(goalPlatform);
        
        auto goal = std::make_shared<Goal5D>(Vec5D(50, 3, 0, 0, 0));
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
 * Level 7: Phase Objects
 * 
 * Teaches: Dimensional occupancy, hypervolume intersection
 * 
 * Puzzle: Objects occupy different hypervolumes in 5D space. You can only
 * interact with them when viewing the correct dimensional perspective where
 * your hypervolume intersects theirs.
 * 
 * Skills: Understanding 5D occupancy, selective interaction, dimensional filtering
 */
class Level7_PhaseObjects : public Level {
public:
    Level7_PhaseObjects() : Level("Phase Objects", 7) {
        description = "Objects exist in different hypervolumes. Phase into their dimension to interact!";
    }

    void initialize() override {
        objects.clear();
        
        // Ground
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, 0, 0, 0, 0),
            Vec5D(70, 1, 40, 40, 40)
        );
        addObject(ground);
        
        // Start
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        addObject(start);
        
        // Phase platforms - thin in different dimensions
        // Only solid when that dimension is visible
        
        // XY-phase platform (thin in Z, W, V)
        auto phaseXY = std::make_shared<Platform5D>(
            Vec5D(10, 2, 0, 0, 0),
            Vec5D(6, 2, 0.5f, 0.5f, 0.5f)
        );
        phaseXY->color = glm::vec3(1.0f, 0.5f, 0.5f);
        addObject(phaseXY);
        
        // XW-phase platform (thin in Y, Z, V)
        auto phaseXW = std::make_shared<Platform5D>(
            Vec5D(18, 2, 0, 0, 0),
            Vec5D(6, 0.5f, 0.5f, 4, 0.5f)
        );
        phaseXW->color = glm::vec3(0.5f, 1.0f, 0.5f);
        addObject(phaseXW);
        
        // XV-phase platform (thin in Y, Z, W)
        auto phaseXV = std::make_shared<Platform5D>(
            Vec5D(26, 2, 0, 0, 0),
            Vec5D(6, 0.5f, 0.5f, 0.5f, 4)
        );
        phaseXV->color = glm::vec3(0.5f, 0.5f, 1.0f);
        addObject(phaseXV);
        
        // YZ-phase platform
        auto phaseYZ = std::make_shared<Platform5D>(
            Vec5D(34, 2, 0, 0, 0),
            Vec5D(0.5f, 4, 4, 0.5f, 0.5f)
        );
        phaseYZ->color = glm::vec3(1.0f, 1.0f, 0.5f);
        addObject(phaseYZ);
        
        // WV-phase platform
        auto phaseWV = std::make_shared<Platform5D>(
            Vec5D(42, 2, 0, 0, 0),
            Vec5D(0.5f, 0.5f, 0.5f, 4, 4)
        );
        phaseWV->color = glm::vec3(1.0f, 0.5f, 1.0f);
        addObject(phaseWV);
        
        // Transitional platforms
        addPlatform(Vec5D(14, 3, 0, 0, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.7f, 0.7f, 0.7f));
        addPlatform(Vec5D(22, 3, 0, 0, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.7f, 0.7f, 0.7f));
        addPlatform(Vec5D(30, 3, 0, 0, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.7f, 0.7f, 0.7f));
        addPlatform(Vec5D(38, 3, 0, 0, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.7f, 0.7f, 0.7f));
        addPlatform(Vec5D(46, 3, 0, 0, 0), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.7f, 0.7f, 0.7f));
        
        // Goal
        auto goalPlatform = std::make_shared<Platform5D>(
            Vec5D(55, 1, 0, 0, 0),
            Vec5D(5, 0.5f, 5, 5, 5)
        );
        addObject(goalPlatform);
        
        auto goal = std::make_shared<Goal5D>(Vec5D(55, 3, 0, 0, 0));
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
