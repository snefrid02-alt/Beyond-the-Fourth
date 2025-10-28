#pragma once

#include "../engine/GameObject5D.hpp"
#include "../engine/Player5D.hpp"
#include <vector>
#include <memory>
#include <string>

/**
 * Level - Represents a game level with objects and puzzles
 */
class Level {
public:
    std::string name;
    std::string description;
    std::vector<std::shared_ptr<GameObject5D>> objects;
    Vec5D playerStartPos;
    int levelNumber;

    Level(const std::string& n, int num) 
        : name(n)
        , levelNumber(num)
        , playerStartPos(0, 2, 0, 0, 0)
    {}

    virtual ~Level() = default;

    /**
     * Initialize level objects
     */
    virtual void initialize() = 0;

    /**
     * Update all objects in the level
     */
    void update(float deltaTime) {
        for (auto& obj : objects) {
            obj->update(deltaTime);
        }
    }

    /**
     * Add an object to the level
     */
    void addObject(std::shared_ptr<GameObject5D> obj) {
        objects.push_back(obj);
    }

    /**
     * Check if level is complete (player reached goal)
     */
    bool isComplete(const Player5D& player) const {
        for (const auto& obj : objects) {
            if (obj->name == "Goal") {
                Goal5D* goal = dynamic_cast<Goal5D*>(obj.get());
                if (goal && goal->contains(player.position)) {
                    return true;
                }
            }
        }
        return false;
    }
};

/**
 * Level 1: Introduction to 5D Space
 * 
 * Teaches: Basic movement, dimension rotation, objects appearing/disappearing
 * 
 * Puzzle: A platform exists in XYZ space but not in XYW space. Player must
 * rotate dimensions to see and use the platform.
 */
class Level1 : public Level {
public:
    Level1() : Level("Introduction to 5D", 1) {
        description = "Learn to move and rotate dimensions. The platform ahead only exists in certain views!";
    }

    void initialize() override {
        objects.clear();
        
        // Ground platform (visible in all dimensions)
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, 0, 0, 0, 0),
            Vec5D(20, 1, 20, 20, 20)
        );
        ground->color = glm::vec3(0.5f, 0.5f, 0.6f);
        addObject(ground);
        
        // Starting platform
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        start->color = glm::vec3(0.7f, 0.7f, 0.8f);
        addObject(start);
        
        // Hidden platform - only visible when viewing XYW or XYV
        // Located at W=5, invisible in standard XYZ view
        auto hiddenPlatform = std::make_shared<Platform5D>(
            Vec5D(8, 1, 0, 5, 0),
            Vec5D(4, 0.5f, 4, 2, 4)
        );
        hiddenPlatform->color = glm::vec3(1.0f, 0.7f, 0.3f);
        addObject(hiddenPlatform);
        
        // Wall to demonstrate 5D bypass
        // This wall blocks in XYZ but can be bypassed via W dimension
        auto wall = std::make_shared<Platform5D>(
            Vec5D(6, 3, 0, 0, 0),
            Vec5D(1, 6, 6, 1, 6)
        );
        wall->color = glm::vec3(0.8f, 0.3f, 0.3f);
        addObject(wall);
        
        // Goal platform
        auto goalPlatform = std::make_shared<Platform5D>(
            Vec5D(15, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        goalPlatform->color = glm::vec3(0.7f, 0.7f, 0.8f);
        addObject(goalPlatform);
        
        // Goal
        auto goal = std::make_shared<Goal5D>(Vec5D(15, 3, 0, 0, 0));
        addObject(goal);
        
        playerStartPos = Vec5D(0, 3, 0, 0, 0);
    }
};

/**
 * Level 2: Moving Platforms in 5D
 * 
 * Teaches: Timing, moving platforms, multiple dimension rotations
 * 
 * Puzzle: Platforms move through different dimensions. Player must rotate
 * view to see and jump on platforms at the right time.
 */
class Level2 : public Level {
public:
    Level2() : Level("5D Platforming", 2) {
        description = "Platforms move through dimensions. Time your jumps carefully!";
    }

    void initialize() override {
        objects.clear();
        
        // Ground
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, 0, 0, 0, 0),
            Vec5D(30, 1, 20, 20, 20)
        );
        addObject(ground);
        
        // Starting platform
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        addObject(start);
        
        // Moving platform 1: Moves in X-Y plane
        auto moving1 = std::make_shared<MovingPlatform5D>(
            Vec5D(5, 1, 0, 0, 0),
            Vec5D(10, 4, 0, 0, 0),
            0.5f
        );
        addObject(moving1);
        
        // Moving platform 2: Moves in W dimension
        // Appears/disappears in XYZ view as it moves through W
        auto moving2 = std::make_shared<MovingPlatform5D>(
            Vec5D(15, 1, 0, -3, 0),
            Vec5D(15, 1, 0, 3, 0),
            0.3f
        );
        moving2->color = glm::vec3(0.9f, 0.6f, 0.9f);
        addObject(moving2);
        
        // Static platform for landing
        auto mid = std::make_shared<Platform5D>(
            Vec5D(20, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        addObject(mid);
        
        // Moving platform 3: Moves in V dimension
        auto moving3 = std::make_shared<MovingPlatform5D>(
            Vec5D(25, 2, 0, 0, -4),
            Vec5D(25, 2, 0, 0, 4),
            0.4f
        );
        moving3->color = glm::vec3(0.6f, 0.9f, 0.6f);
        addObject(moving3);
        
        // Goal platform
        auto goalPlatform = std::make_shared<Platform5D>(
            Vec5D(30, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        addObject(goalPlatform);
        
        // Goal
        auto goal = std::make_shared<Goal5D>(Vec5D(30, 3, 0, 0, 0));
        addObject(goal);
        
        playerStartPos = Vec5D(0, 3, 0, 0, 0);
    }
};

/**
 * Level 3: The Hypercube Maze
 * 
 * Teaches: Complex 5D topology, strategic dimension rotation
 * 
 * Puzzle: A maze that only makes sense when viewing specific dimensions.
 * Walls appear and disappear based on which 3D slice you're viewing.
 */
class Level3 : public Level {
public:
    Level3() : Level("Hypercube Maze", 3) {
        description = "Navigate the maze by rotating through dimensions. The path changes with each view!";
    }

    void initialize() override {
        objects.clear();
        
        // Ground
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, 0, 0, 0, 0),
            Vec5D(40, 1, 40, 40, 40)
        );
        addObject(ground);
        
        // Start platform
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(4, 0.5f, 4, 4, 4)
        );
        addObject(start);
        
        // Create maze walls that exist in different dimensional configurations
        // Wall 1: Blocks in XYZ view (W=0, V=0)
        addMazeWall(Vec5D(5, 2, 0, 0, 0), Vec5D(1, 4, 10, 1, 10));
        
        // Wall 2: Blocks in XYW view (Z=0, V=0)
        addMazeWall(Vec5D(10, 2, 0, 0, 0), Vec5D(1, 4, 1, 10, 10));
        
        // Wall 3: Blocks in XYV view (Z=0, W=0)
        addMazeWall(Vec5D(15, 2, 0, 0, 0), Vec5D(1, 4, 10, 10, 1));
        
        // Platforms at different 5D locations
        addPlatform(Vec5D(8, 1, 5, 0, 0), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.8f, 0.6f, 0.6f));
        addPlatform(Vec5D(12, 1, 0, 5, 0), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.6f, 0.8f, 0.6f));
        addPlatform(Vec5D(18, 1, 0, 0, 5), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.6f, 0.6f, 0.8f));
        
        // Complex structure: appears different from each angle
        addPlatform(Vec5D(22, 3, 3, 3, 3), Vec5D(2, 0.5f, 2, 2, 2), glm::vec3(0.9f, 0.9f, 0.5f));
        addPlatform(Vec5D(25, 1, 5, -2, 3), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.9f, 0.5f, 0.9f));
        
        // Goal platform - requires navigating through multiple dimensions
        auto goalPlatform = std::make_shared<Platform5D>(
            Vec5D(30, 1, 0, 0, 0),
            Vec5D(5, 0.5f, 5, 5, 5)
        );
        goalPlatform->color = glm::vec3(0.9f, 0.9f, 0.9f);
        addObject(goalPlatform);
        
        // Goal
        auto goal = std::make_shared<Goal5D>(Vec5D(30, 3, 0, 0, 0));
        addObject(goal);
        
        playerStartPos = Vec5D(0, 3, 0, 0, 0);
    }

private:
    void addMazeWall(const Vec5D& pos, const Vec5D& size) {
        auto wall = std::make_shared<Platform5D>(pos, size);
        wall->color = glm::vec3(0.7f, 0.3f, 0.3f);
        addObject(wall);
    }

    void addPlatform(const Vec5D& pos, const Vec5D& size, const glm::vec3& color) {
        auto platform = std::make_shared<Platform5D>(pos, size);
        platform->color = color;
        addObject(platform);
    }
};
