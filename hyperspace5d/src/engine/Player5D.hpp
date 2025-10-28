#pragma once

#include "GameObject5D.hpp"
#include "../core/DimensionState.hpp"
#include <glm/glm.hpp>

/**
 * Player5D - The player character existing in 5D space
 * 
 * Handles player movement, jumping, dashing, and wall-sliding mechanics.
 * Movement is controlled in the currently visible 3D slice.
 */
class Player5D : public GameObject5D {
public:
    // Movement parameters
    float moveSpeed;
    float jumpStrength;
    float dashSpeed;
    float dashDuration;
    float dashCooldown;
    float gravity;
    float maxFallSpeed;
    float wallSlideSpeed;
    
    // State
    bool isGrounded;
    bool isOnWall;
    bool isDashing;
    bool canDash;
    float dashTimer;
    float dashCooldownTimer;
    Vec5D wallNormal;
    
    // Input state
    glm::vec3 moveInput;  // Movement in current 3D slice
    bool jumpPressed;
    bool dashPressed;
    
    // Reference to dimension state (not owned)
    const DimensionState* dimState;

    Player5D() 
        : moveSpeed(5.0f)
        , jumpStrength(8.0f)
        , dashSpeed(15.0f)
        , dashDuration(0.2f)
        , dashCooldown(1.0f)
        , gravity(20.0f)
        , maxFallSpeed(20.0f)
        , wallSlideSpeed(2.0f)
        , isGrounded(false)
        , isOnWall(false)
        , isDashing(false)
        , canDash(true)
        , dashTimer(0.0f)
        , dashCooldownTimer(0.0f)
        , moveInput(0.0f)
        , jumpPressed(false)
        , dashPressed(false)
        , dimState(nullptr)
    {
        name = "Player";
        color = glm::vec3(0.3f, 0.6f, 1.0f);
        size = Vec5D(0.8f, 1.6f, 0.8f, 0.8f, 0.8f);
    }

    void setDimensionState(const DimensionState* state) {
        dimState = state;
    }

    void update(float deltaTime) override {
        // Update timers
        if (dashCooldownTimer > 0.0f) {
            dashCooldownTimer -= deltaTime;
            if (dashCooldownTimer <= 0.0f) {
                canDash = true;
            }
        }

        if (isDashing) {
            updateDash(deltaTime);
        } else {
            updateNormalMovement(deltaTime);
        }

        // Reset input flags
        jumpPressed = false;
        dashPressed = false;
    }

    void handleJump() {
        if (isGrounded || isOnWall) {
            // Apply jump velocity in the "up" direction of current view
            if (dimState) {
                int upDim = dimState->visibleDims[1];  // Y axis of current view
                velocity[upDim] = jumpStrength;
                
                // Wall jump: also push away from wall
                if (isOnWall && !isGrounded) {
                    velocity = velocity + wallNormal * (jumpStrength * 0.5f);
                }
            }
            isGrounded = false;
            isOnWall = false;
        }
    }

    void handleDash() {
        if (canDash && !isDashing && moveInput.length() > 0.1f) {
            isDashing = true;
            canDash = false;
            dashTimer = dashDuration;
            dashCooldownTimer = dashCooldown;
            
            // Dash in the direction of movement
            if (dimState) {
                Vec5D dashDir;
                glm::vec3 normalizedInput = glm::normalize(moveInput);
                
                // Map 3D input to 5D movement in current visible dimensions
                dashDir[dimState->visibleDims[0]] = normalizedInput.x;
                dashDir[dimState->visibleDims[1]] = normalizedInput.y;
                dashDir[dimState->visibleDims[2]] = normalizedInput.z;
                
                velocity = dashDir.normalized() * dashSpeed;
            }
        }
    }

    void setMoveInput(const glm::vec3& input) {
        moveInput = input;
    }

    void setJumpPressed() {
        if (!jumpPressed) {
            jumpPressed = true;
            handleJump();
        }
    }

    void setDashPressed() {
        if (!dashPressed) {
            dashPressed = true;
            handleDash();
        }
    }

private:
    void updateNormalMovement(float deltaTime) {
        if (!dimState) return;

        // Apply movement input in the visible dimensions
        Vec5D inputVel;
        inputVel[dimState->visibleDims[0]] = moveInput.x * moveSpeed;
        inputVel[dimState->visibleDims[2]] = moveInput.z * moveSpeed;
        
        // Apply horizontal velocity
        velocity[dimState->visibleDims[0]] = inputVel[dimState->visibleDims[0]];
        velocity[dimState->visibleDims[2]] = inputVel[dimState->visibleDims[2]];
        
        // Apply gravity in the "up" dimension
        int upDim = dimState->visibleDims[1];
        if (!isGrounded) {
            velocity[upDim] -= gravity * deltaTime;
            
            // Terminal velocity
            if (velocity[upDim] < -maxFallSpeed) {
                velocity[upDim] = -maxFallSpeed;
            }
        }
        
        // Wall sliding
        if (isOnWall && !isGrounded && velocity[upDim] < 0) {
            velocity[upDim] = std::max(velocity[upDim], -wallSlideSpeed);
        }
        
        // Update position
        position += velocity * deltaTime;
    }

    void updateDash(float deltaTime) {
        dashTimer -= deltaTime;
        
        if (dashTimer <= 0.0f) {
            isDashing = false;
            // Reduce velocity after dash
            velocity = velocity * 0.5f;
        }
        
        // Continue moving in dash direction (velocity already set)
        position += velocity * deltaTime;
    }
};
