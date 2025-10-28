/*
 * This is free and unencumbered software released into the public domain.
 * For more information, please refer to <http://unlicense.org/>
 */

#pragma once

#include "Level.hpp"
#include "../engine/GameObject5D.hpp"
#include <cmath>
#include <vector>

/**
 * BossCore - Individual vulnerable core of The Pentarch
 * 
 * Each core is only vulnerable when viewed from a specific dimensional perspective.
 */
class BossCore : public GameObject5D {
public:
    int vulnerableDim1, vulnerableDim2, vulnerableDim3;
    bool isDestroyed;
    float health;
    float maxHealth;
    float pulseTime;
    
    BossCore(const Vec5D& pos, int d1, int d2, int d3) 
        : vulnerableDim1(d1)
        , vulnerableDim2(d2)
        , vulnerableDim3(d3)
        , isDestroyed(false)
        , health(100.0f)
        , maxHealth(100.0f)
        , pulseTime(0.0f)
    {
        position = pos;
        size = Vec5D(2, 2, 2, 2, 2);
        isStatic = false;
        isSolid = true;
        name = "BossCore";
    }
    
    void update(float deltaTime) override {
        if (isDestroyed) {
            opacity = 0.2f;
            return;
        }
        
        pulseTime += deltaTime * 3.0f;
        
        // Pulsing effect
        float pulse = 0.7f + 0.3f * std::sin(pulseTime);
        opacity = pulse;
        
        // Color based on health
        float healthRatio = health / maxHealth;
        color = glm::vec3(
            1.0f - healthRatio * 0.5f,
            healthRatio,
            healthRatio * 0.5f
        );
    }
    
    bool isVulnerableFromView(int d1, int d2, int d3) const {
        if (isDestroyed) return false;
        return (d1 == vulnerableDim1 && d2 == vulnerableDim2 && d3 == vulnerableDim3);
    }
    
    void takeDamage(float amount) {
        if (isDestroyed) return;
        health -= amount;
        if (health <= 0) {
            health = 0;
            isDestroyed = true;
        }
    }
};

/**
 * BossProjectile - 5D projectile that appears/disappears based on view
 */
class BossProjectile : public GameObject5D {
public:
    Vec5D direction;
    float speed;
    float lifetime;
    float maxLifetime;
    
    BossProjectile(const Vec5D& pos, const Vec5D& dir, float spd)
        : direction(dir.normalized())
        , speed(spd)
        , lifetime(0.0f)
        , maxLifetime(5.0f)
    {
        position = pos;
        velocity = direction * speed;
        size = Vec5D(0.8f, 0.8f, 0.8f, 0.8f, 0.8f);
        isStatic = false;
        isSolid = true;
        color = glm::vec3(1.0f, 0.2f, 0.2f);
        name = "Projectile";
    }
    
    void update(float deltaTime) override {
        GameObject5D::update(deltaTime);
        lifetime += deltaTime;
        
        // Fade out as lifetime approaches max
        opacity = 1.0f - (lifetime / maxLifetime);
    }
    
    bool isExpired() const {
        return lifetime >= maxLifetime;
    }
};

/**
 * Level 11: The Pentarch - Final Boss
 * 
 * Boss Concept: A 5D entity with 5 cores, each vulnerable from one specific
 * dimensional view (XYZ, XYW, XYV, XZW, YZW). Must be defeated by attacking
 * all cores while dodging 5D attacks and navigating dynamic geometry.
 * 
 * Boss Phases:
 * - Phase 1: All 5 cores active, slow attacks, stable arena
 * - Phase 2: 3-4 cores active, medium attacks, some geometry changes
 * - Phase 3: 1-2 cores active, fast attacks, dynamic arena
 * - Phase 4: Last core, extreme aggression, chaotic geometry
 * 
 * Victory: Destroy all 5 cores
 */
class Level11_ThePentarch : public Level {
private:
    std::vector<std::shared_ptr<BossCore>> cores;
    std::vector<std::shared_ptr<BossProjectile>> projectiles;
    
    float bossPhaseTimer;
    int currentPhase;
    float attackCooldown;
    float attackInterval;
    float geometryChangeTimer;
    
    // Arena platforms that change during fight
    std::vector<std::shared_ptr<MovingPlatform5D>> dynamicPlatforms;

public:
    Level11_ThePentarch() : Level("The Pentarch", 11) {
        description = "Face The Pentarch - master of all five dimensions. Destroy its cores to win!";
        bossPhaseTimer = 0.0f;
        currentPhase = 1;
        attackCooldown = 0.0f;
        attackInterval = 2.0f;
        geometryChangeTimer = 0.0f;
    }

    void initialize() override {
        objects.clear();
        cores.clear();
        projectiles.clear();
        dynamicPlatforms.clear();
        
        bossPhaseTimer = 0.0f;
        currentPhase = 1;
        attackCooldown = 0.0f;
        geometryChangeTimer = 0.0f;
        
        // Arena ground
        auto ground = std::make_shared<Platform5D>(
            Vec5D(0, 0, 0, 0, 0),
            Vec5D(80, 1, 80, 80, 80)
        );
        ground->color = glm::vec3(0.2f, 0.2f, 0.3f);
        addObject(ground);
        
        // Start platform
        auto start = std::make_shared<Platform5D>(
            Vec5D(0, 1, 0, 0, 0),
            Vec5D(5, 0.5f, 5, 5, 5)
        );
        start->color = glm::vec3(0.5f, 0.5f, 0.6f);
        addObject(start);
        
        // Create The Pentarch's 5 cores
        // Each core is vulnerable from a different dimensional view
        
        // Core 1: Vulnerable in XYZ view (standard 3D)
        auto core1 = std::make_shared<BossCore>(Vec5D(20, 8, 0, 0, 0), 0, 1, 2);
        core1->color = glm::vec3(1.0f, 0.3f, 0.3f);
        cores.push_back(core1);
        addObject(core1);
        
        // Core 2: Vulnerable in XYW view (4D perspective)
        auto core2 = std::make_shared<BossCore>(Vec5D(20, 8, 0, 15, 0), 0, 1, 3);
        core2->color = glm::vec3(0.3f, 1.0f, 0.3f);
        cores.push_back(core2);
        addObject(core2);
        
        // Core 3: Vulnerable in XYV view (5D perspective)
        auto core3 = std::make_shared<BossCore>(Vec5D(20, 8, 0, 0, 15), 0, 1, 4);
        core3->color = glm::vec3(0.3f, 0.3f, 1.0f);
        cores.push_back(core3);
        addObject(core3);
        
        // Core 4: Vulnerable in XZW view
        auto core4 = std::make_shared<BossCore>(Vec5D(20, 8, 12, 8, 0), 0, 2, 3);
        core4->color = glm::vec3(1.0f, 1.0f, 0.3f);
        cores.push_back(core4);
        addObject(core4);
        
        // Core 5: Vulnerable in YZW view
        auto core5 = std::make_shared<BossCore>(Vec5D(20, 12, 8, 8, 0), 1, 2, 3);
        core5->color = glm::vec3(1.0f, 0.3f, 1.0f);
        cores.push_back(core5);
        addObject(core5);
        
        // Create arena platforms
        createArenaPlatforms();
        
        // Goal (appears after all cores destroyed)
        auto goal = std::make_shared<Goal5D>(Vec5D(40, 3, 0, 0, 0));
        goal->isVisible = false;  // Hidden until victory
        addObject(goal);
        
        playerStartPos = Vec5D(0, 3, 0, 0, 0);
    }

    void update(float deltaTime) override {
        Level::update(deltaTime);
        
        bossPhaseTimer += deltaTime;
        attackCooldown -= deltaTime;
        geometryChangeTimer += deltaTime;
        
        // Update boss cores
        for (auto& core : cores) {
            core->update(deltaTime);
        }
        
        // Update projectiles
        for (auto it = projectiles.begin(); it != projectiles.end();) {
            (*it)->update(deltaTime);
            if ((*it)->isExpired()) {
                // Remove from objects list too
                auto objIt = std::find(objects.begin(), objects.end(), *it);
                if (objIt != objects.end()) {
                    objects.erase(objIt);
                }
                it = projectiles.erase(it);
            } else {
                ++it;
            }
        }
        
        // Determine current phase based on remaining cores
        int activeCores = 0;
        for (const auto& core : cores) {
            if (!core->isDestroyed) activeCores++;
        }
        
        if (activeCores == 0) {
            // Victory! Show goal
            for (auto& obj : objects) {
                if (obj->name == "Goal") {
                    obj->isVisible = true;
                }
            }
        } else {
            // Boss behavior based on phase
            if (activeCores == 5) currentPhase = 1;
            else if (activeCores >= 3) currentPhase = 2;
            else if (activeCores >= 2) currentPhase = 3;
            else currentPhase = 4;
            
            // Update attack interval based on phase
            attackInterval = 3.0f - (currentPhase - 1) * 0.5f;
            
            // Boss attacks
            if (attackCooldown <= 0.0f) {
                bossAttack();
                attackCooldown = attackInterval;
            }
            
            // Dynamic geometry changes (more frequent in later phases)
            if (geometryChangeTimer > 5.0f / currentPhase) {
                updateArenaGeometry();
                geometryChangeTimer = 0.0f;
            }
        }
    }

private:
    void createArenaPlatforms() {
        // Static safe platforms
        addPlatform(Vec5D(10, 2, 0, 0, 0), Vec5D(4, 0.5f, 4, 4, 4), glm::vec3(0.6f, 0.6f, 0.7f));
        addPlatform(Vec5D(30, 2, 0, 0, 0), Vec5D(4, 0.5f, 4, 4, 4), glm::vec3(0.6f, 0.6f, 0.7f));
        addPlatform(Vec5D(20, 2, 10, 0, 0), Vec5D(4, 0.5f, 4, 4, 4), glm::vec3(0.6f, 0.6f, 0.7f));
        addPlatform(Vec5D(20, 2, -10, 0, 0), Vec5D(4, 0.5f, 4, 4, 4), glm::vec3(0.6f, 0.6f, 0.7f));
        
        // Dynamic moving platforms
        auto movingPlat1 = std::make_shared<MovingPlatform5D>(
            Vec5D(15, 4, 0, 0, 0),
            Vec5D(25, 4, 0, 10, 0),
            0.3f
        );
        movingPlat1->color = glm::vec3(0.7f, 0.5f, 0.7f);
        dynamicPlatforms.push_back(movingPlat1);
        addObject(movingPlat1);
        
        auto movingPlat2 = std::make_shared<MovingPlatform5D>(
            Vec5D(20, 4, 5, 0, 0),
            Vec5D(20, 4, 5, 0, 10),
            0.4f
        );
        movingPlat2->color = glm::vec3(0.5f, 0.7f, 0.7f);
        dynamicPlatforms.push_back(movingPlat2);
        addObject(movingPlat2);
        
        // Platforms in different dimensional layers
        addPlatform(Vec5D(20, 5, 0, 8, 0), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.5f, 0.8f, 0.5f));
        addPlatform(Vec5D(20, 5, 0, 0, 8), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.5f, 0.5f, 0.8f));
        addPlatform(Vec5D(20, 6, 0, 8, 8), Vec5D(3, 0.5f, 3, 3, 3), glm::vec3(0.8f, 0.5f, 0.8f));
    }

    void addPlatform(const Vec5D& pos, const Vec5D& size, const glm::vec3& color) {
        auto platform = std::make_shared<Platform5D>(pos, size);
        platform->color = color;
        addObject(platform);
    }

    void bossAttack() {
        // Boss fires projectiles from active cores toward player
        // In a full implementation, would get actual player position
        Vec5D playerApproxPos(0, 3, 0, 0, 0);  // Approximate player location
        
        for (auto& core : cores) {
            if (core->isDestroyed) continue;
            
            // Fire projectile toward player (with some randomness)
            Vec5D direction = playerApproxPos - core->position;
            
            // Add randomness based on phase (more accurate in later phases)
            float randomness = 5.0f / currentPhase;
            direction.x += (std::rand() % 100 / 50.0f - 1.0f) * randomness;
            direction.y += (std::rand() % 100 / 50.0f - 1.0f) * randomness;
            direction.z += (std::rand() % 100 / 50.0f - 1.0f) * randomness;
            
            float projectileSpeed = 8.0f + currentPhase * 2.0f;
            auto projectile = std::make_shared<BossProjectile>(
                core->position,
                direction,
                projectileSpeed
            );
            
            projectiles.push_back(projectile);
            addObject(projectile);
        }
        
        // In later phases, create hyperwalls
        if (currentPhase >= 3 && std::rand() % 3 == 0) {
            create5DHyperwall();
        }
    }

    void create5DHyperwall() {
        // Create a 4D "wall" that blocks movement
        // Random orientation in 5D space
        int fixedDim = std::rand() % 5;
        float fixedValue = (std::rand() % 20) - 10.0f;
        
        Vec5D wallPos(10, 2, 0, 0, 0);
        Vec5D wallSize(20, 4, 20, 20, 20);
        
        wallPos[fixedDim] = fixedValue;
        wallSize[fixedDim] = 0.5f;  // Thin in one dimension
        
        auto hyperwall = std::make_shared<Platform5D>(wallPos, wallSize);
        hyperwall->color = glm::vec3(0.8f, 0.2f, 0.2f);
        hyperwall->opacity = 0.6f;
        addObject(hyperwall);
        
        // These walls would need to be removed after some time
        // In full implementation, add a timer system
    }

    void updateArenaGeometry() {
        // Change moving platform speeds/directions based on phase
        for (auto& plat : dynamicPlatforms) {
            plat->speed = 0.3f + currentPhase * 0.2f;
            
            // In final phase, platforms become more chaotic
            if (currentPhase == 4) {
                // Randomly swap start/end positions
                if (std::rand() % 2 == 0) {
                    std::swap(plat->startPos, plat->endPos);
                }
            }
        }
    }
};
