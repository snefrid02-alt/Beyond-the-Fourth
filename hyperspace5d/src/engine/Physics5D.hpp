#pragma once

#include "GameObject5D.hpp"
#include "Player5D.hpp"
#include <vector>
#include <memory>

/**
 * Physics5D - Physics engine for 5D space
 * 
 * Handles collision detection and resolution in full 5D space.
 * Uses AABB (Axis-Aligned Bounding Box) collision detection.
 */
class Physics5D {
public:
    struct CollisionInfo {
        GameObject5D* object;
        Vec5D normal;           // Collision normal in 5D space
        float penetration;      // How far objects overlap
        int collisionDim;       // Primary dimension of collision
        
        CollisionInfo() : object(nullptr), penetration(0.0f), collisionDim(0) {}
    };

    /**
     * Check collision between two objects
     */
    static bool checkCollision(const GameObject5D& a, const GameObject5D& b, CollisionInfo* info = nullptr) {
        if (!a.intersects(b)) {
            return false;
        }

        if (info) {
            // Calculate collision details
            Vec5D centerA = a.position;
            Vec5D centerB = b.position;
            Vec5D diff = centerA - centerB;
            
            // Find the dimension with minimum penetration (that's the collision axis)
            float minPenetration = std::numeric_limits<float>::max();
            int collisionDim = 0;
            
            for (int i = 0; i < 5; ++i) {
                float halfSizeA = a.size[i] * 0.5f;
                float halfSizeB = b.size[i] * 0.5f;
                float penetration = (halfSizeA + halfSizeB) - std::abs(diff[i]);
                
                if (penetration < minPenetration) {
                    minPenetration = penetration;
                    collisionDim = i;
                }
            }
            
            // Create normal vector pointing from B to A
            Vec5D normal;
            normal[collisionDim] = (diff[collisionDim] > 0) ? 1.0f : -1.0f;
            
            info->normal = normal;
            info->penetration = minPenetration;
            info->collisionDim = collisionDim;
        }

        return true;
    }

    /**
     * Resolve collision between player and an object
     */
    static void resolvePlayerCollision(Player5D& player, GameObject5D& object, const CollisionInfo& collision) {
        if (!object.isSolid) return;

        // Push player out of the object
        player.position += collision.normal * collision.penetration;
        
        // Check if this is a ground collision (in the "up" dimension)
        if (player.dimState) {
            int upDim = player.dimState->visibleDims[1];
            
            if (collision.collisionDim == upDim) {
                if (collision.normal[upDim] > 0) {
                    // Collision from below (standing on ground)
                    player.isGrounded = true;
                    player.velocity[upDim] = std::max(0.0f, player.velocity[upDim]);
                } else {
                    // Collision from above (hit ceiling)
                    player.velocity[upDim] = std::min(0.0f, player.velocity[upDim]);
                }
            } else {
                // Wall collision
                player.isOnWall = true;
                player.wallNormal = collision.normal;
                
                // Stop velocity in collision direction
                float velocityInNormal = player.velocity.dot(collision.normal);
                if (velocityInNormal < 0) {
                    player.velocity -= collision.normal * velocityInNormal;
                }
            }
        }
    }

    /**
     * Apply physics to player and check collisions
     */
    static void updatePlayer(Player5D& player, const std::vector<std::shared_ptr<GameObject5D>>& objects, float deltaTime) {
        // Reset collision flags
        player.isGrounded = false;
        player.isOnWall = false;
        
        // Store old position for collision response
        Vec5D oldPos = player.position;
        
        // Update player (applies velocity)
        player.update(deltaTime);
        
        // Check collisions with all objects
        for (auto& obj : objects) {
            if (obj.get() == &player) continue;
            if (!obj->isSolid) continue;
            
            CollisionInfo collision;
            if (checkCollision(player, *obj, &collision)) {
                collision.object = obj.get();
                resolvePlayerCollision(player, *obj, collision);
            }
        }
    }

    /**
     * Cast a ray through 5D space
     * Used for visibility checks and advanced collision detection
     */
    static bool rayCast(const Vec5D& origin, const Vec5D& direction, float maxDistance,
                       const std::vector<std::shared_ptr<GameObject5D>>& objects,
                       GameObject5D** hitObject, Vec5D* hitPoint) {
        
        float closestDistance = maxDistance;
        GameObject5D* closest = nullptr;
        Vec5D closestPoint;
        
        for (auto& obj : objects) {
            if (!obj->isSolid) continue;
            
            // Simplified ray-box intersection in 5D
            // For each dimension, calculate entry and exit times
            float tMin = 0.0f;
            float tMax = maxDistance;
            
            Vec5D objMin = obj->getMin();
            Vec5D objMax = obj->getMax();
            
            for (int i = 0; i < 5; ++i) {
                if (std::abs(direction[i]) > 1e-6f) {
                    float t1 = (objMin[i] - origin[i]) / direction[i];
                    float t2 = (objMax[i] - origin[i]) / direction[i];
                    
                    if (t1 > t2) std::swap(t1, t2);
                    
                    tMin = std::max(tMin, t1);
                    tMax = std::min(tMax, t2);
                    
                    if (tMin > tMax) break;
                }
            }
            
            if (tMin <= tMax && tMin < closestDistance && tMin >= 0) {
                closestDistance = tMin;
                closest = obj.get();
                closestPoint = origin + direction * tMin;
            }
        }
        
        if (closest) {
            if (hitObject) *hitObject = closest;
            if (hitPoint) *hitPoint = closestPoint;
            return true;
        }
        
        return false;
    }

    /**
     * Check if a point is inside any solid object
     */
    static bool pointInSolid(const Vec5D& point, const std::vector<std::shared_ptr<GameObject5D>>& objects) {
        for (const auto& obj : objects) {
            if (obj->isSolid && obj->contains(point)) {
                return true;
            }
        }
        return false;
    }
};
