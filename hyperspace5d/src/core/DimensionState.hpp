#pragma once

#include "Matrix5D.hpp"
#include <string>
#include <array>

/**
 * DimensionState - Manages which 3D slice of 5D space is currently visible
 * 
 * In our 5D game, the player can only see 3 dimensions at once. This class
 * tracks which 3 dimensions are currently being viewed and manages smooth
 * transitions between different dimensional views.
 * 
 * The five dimensions are indexed as:
 * 0 = X, 1 = Y, 2 = Z, 3 = W, 4 = V
 */
class DimensionState {
public:
    // Current visible dimensions (indices 0-4)
    std::array<int, 3> visibleDims;
    
    // Target dimensions (for smooth transitions)
    std::array<int, 3> targetDims;
    
    // Rotation matrix representing current orientation in 5D space
    Matrix5D rotationMatrix;
    
    // Target rotation matrix (for interpolation)
    Matrix5D targetRotation;
    
    // Transition progress (0 = at current, 1 = at target)
    float transitionProgress;
    
    // Transition speed (units per second)
    float transitionSpeed;

    DimensionState() 
        : visibleDims({0, 1, 2})  // Start with XYZ visible
        , targetDims({0, 1, 2})
        , transitionProgress(1.0f)
        , transitionSpeed(2.0f)
    {
        rotationMatrix.identity();
        targetRotation.identity();
    }

    /**
     * Rotate to show a different set of dimensions.
     * This initiates a smooth transition.
     * 
     * @param dim1, dim2, dim3 The three dimensions to show (0-4)
     */
    void rotateToDimensions(int dim1, int dim2, int dim3) {
        if (transitionProgress < 1.0f) {
            // Already transitioning, complete current transition first
            completeTransition();
        }
        
        targetDims = {dim1, dim2, dim3};
        transitionProgress = 0.0f;
        
        // Calculate target rotation matrix
        targetRotation = calculateRotationToDimensions(dim1, dim2, dim3);
    }

    /**
     * Rotate the view in a specific 2D plane of 5D space.
     * This is used for player-controlled rotation.
     * 
     * @param axis1, axis2 The two axes defining the rotation plane
     * @param angle The rotation angle in radians
     */
    void rotateInPlane(int axis1, int axis2, float angle) {
        Matrix5D rotation = Matrix5D::rotation(axis1, axis2, angle);
        rotationMatrix = rotation * rotationMatrix;
        targetRotation = rotationMatrix;
        transitionProgress = 1.0f;
    }

    /**
     * Update transition animation.
     * 
     * @param deltaTime Time since last frame in seconds
     */
    void update(float deltaTime) {
        if (transitionProgress < 1.0f) {
            transitionProgress += transitionSpeed * deltaTime;
            if (transitionProgress >= 1.0f) {
                transitionProgress = 1.0f;
                rotationMatrix = targetRotation;
                visibleDims = targetDims;
            }
        }
    }

    /**
     * Get the current interpolated rotation matrix.
     * During transitions, this smoothly interpolates between current and target.
     */
    Matrix5D getCurrentRotation() const {
        if (transitionProgress >= 1.0f) {
            return rotationMatrix;
        }
        
        // Simple linear interpolation of matrix elements
        // For a more sophisticated implementation, use quaternion-like interpolation
        Matrix5D result;
        float t = smoothStep(transitionProgress);
        
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                result.m[i][j] = rotationMatrix.m[i][j] * (1.0f - t) + 
                                  targetRotation.m[i][j] * t;
            }
        }
        
        return result;
    }

    /**
     * Get a human-readable name for the current dimensional view.
     */
    std::string getCurrentViewName() const {
        static const char* dimNames[] = {"X", "Y", "Z", "W", "V"};
        return std::string(dimNames[visibleDims[0]]) + 
               dimNames[visibleDims[1]] + 
               dimNames[visibleDims[2]] + " View";
    }

    bool isTransitioning() const {
        return transitionProgress < 1.0f;
    }

private:
    void completeTransition() {
        transitionProgress = 1.0f;
        rotationMatrix = targetRotation;
        visibleDims = targetDims;
    }

    /**
     * Calculate a rotation matrix that will make the specified dimensions visible.
     * This is a simplified version - a full implementation would need to consider
     * the current orientation and find the shortest rotation path.
     */
    Matrix5D calculateRotationToDimensions(int dim1, int dim2, int dim3) {
        // For simplicity, we'll create a permutation-like rotation
        // A full implementation would use more sophisticated rotation composition
        Matrix5D rot;
        rot.identity();
        
        // This is a placeholder - real implementation would compute
        // the rotation that aligns the standard XYZ axes with the target dimensions
        return rot;
    }

    /**
     * Smooth step interpolation function for smoother transitions.
     */
    float smoothStep(float t) const {
        return t * t * (3.0f - 2.0f * t);
    }
};
