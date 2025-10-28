#pragma once

#include "../core/Vec5D.hpp"
#include <glm/glm.hpp>
#include <string>
#include <memory>

/**
 * GameObject5D - Base class for all objects existing in 5D space
 * 
 * All game entities inherit from this: player, platforms, obstacles, etc.
 */
class GameObject5D {
public:
    Vec5D position;           // Position in 5D space
    Vec5D velocity;           // Velocity in 5D space
    Vec5D size;               // Bounding box size in each dimension
    
    glm::vec3 color;          // Base color
    float opacity;            // Transparency (0-1)
    
    bool isStatic;            // Static objects don't move
    bool isSolid;             // Solid objects have collision
    bool isVisible;           // Visibility flag
    
    std::string name;         // Object identifier
    int id;                   // Unique ID

    GameObject5D()
        : position()
        , velocity()
        , size(0.5f, 0.5f, 0.5f, 0.5f, 0.5f)
        , color(1.0f, 1.0f, 1.0f)
        , opacity(1.0f)
        , isStatic(false)
        , isSolid(true)
        , isVisible(true)
        , name("GameObject")
        , id(0)
    {}

    virtual ~GameObject5D() = default;

    /**
     * Update object physics and logic
     */
    virtual void update(float deltaTime) {
        if (!isStatic) {
            position += velocity * deltaTime;
        }
    }

    /**
     * Check if this object intersects another in 5D space
     */
    bool intersects(const GameObject5D& other) const {
        // AABB (Axis-Aligned Bounding Box) collision in 5D
        for (int i = 0; i < 5; ++i) {
            float min1 = position[i] - size[i] * 0.5f;
            float max1 = position[i] + size[i] * 0.5f;
            float min2 = other.position[i] - other.size[i] * 0.5f;
            float max2 = other.position[i] + other.size[i] * 0.5f;
            
            if (max1 < min2 || max2 < min1) {
                return false;  // No overlap in this dimension
            }
        }
        return true;  // Overlap in all 5 dimensions
    }

    /**
     * Get the minimum corner of the bounding box
     */
    Vec5D getMin() const {
        return position - size * 0.5f;
    }

    /**
     * Get the maximum corner of the bounding box
     */
    Vec5D getMax() const {
        return position + size * 0.5f;
    }

    /**
     * Check if a point is inside this object
     */
    bool contains(const Vec5D& point) const {
        Vec5D min = getMin();
        Vec5D max = getMax();
        
        for (int i = 0; i < 5; ++i) {
            if (point[i] < min[i] || point[i] > max[i]) {
                return false;
            }
        }
        return true;
    }
};

/**
 * Platform5D - A solid platform in 5D space
 */
class Platform5D : public GameObject5D {
public:
    Platform5D() {
        isStatic = true;
        isSolid = true;
        color = glm::vec3(0.7f, 0.7f, 0.8f);
        name = "Platform";
    }

    Platform5D(const Vec5D& pos, const Vec5D& sz) : Platform5D() {
        position = pos;
        size = sz;
    }
};

/**
 * Goal5D - Level completion goal
 */
class Goal5D : public GameObject5D {
public:
    bool activated;

    Goal5D() : activated(false) {
        isStatic = true;
        isSolid = false;
        color = glm::vec3(0.2f, 1.0f, 0.3f);
        name = "Goal";
        size = Vec5D(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    }

    Goal5D(const Vec5D& pos) : Goal5D() {
        position = pos;
    }

    void update(float deltaTime) override {
        // Pulsating effect
        static float time = 0.0f;
        time += deltaTime;
        opacity = 0.7f + 0.3f * std::sin(time * 3.0f);
    }
};

/**
 * MovingPlatform5D - A platform that moves in 5D space
 */
class MovingPlatform5D : public Platform5D {
public:
    Vec5D startPos;
    Vec5D endPos;
    float speed;
    float progress;
    bool movingForward;

    MovingPlatform5D() 
        : speed(1.0f)
        , progress(0.0f)
        , movingForward(true)
    {
        isStatic = false;
        name = "MovingPlatform";
        color = glm::vec3(0.8f, 0.6f, 0.9f);
    }

    MovingPlatform5D(const Vec5D& start, const Vec5D& end, float spd)
        : MovingPlatform5D()
    {
        startPos = start;
        endPos = end;
        position = start;
        speed = spd;
    }

    void update(float deltaTime) override {
        // Move between start and end positions
        if (movingForward) {
            progress += speed * deltaTime;
            if (progress >= 1.0f) {
                progress = 1.0f;
                movingForward = false;
            }
        } else {
            progress -= speed * deltaTime;
            if (progress <= 0.0f) {
                progress = 0.0f;
                movingForward = true;
            }
        }

        // Smooth interpolation
        float t = progress * progress * (3.0f - 2.0f * progress);
        position = startPos + (endPos - startPos) * t;
        
        // Calculate velocity for proper physics interaction
        velocity = (endPos - startPos) * speed * (movingForward ? 1.0f : -1.0f);
    }
};
