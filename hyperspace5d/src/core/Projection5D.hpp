#pragma once

#include "Vec5D.hpp"
#include "Matrix5D.hpp"
#include "DimensionState.hpp"
#include <glm/glm.hpp>
#include <vector>

/**
 * Projection5D - Handles projection from 5D space to 3D viewable space
 * 
 * This is the core rendering concept: we take 5D geometry and project it
 * down to 3D so it can be displayed. The projection method depends on
 * which dimensions are currently visible.
 * 
 * Mathematical Approach:
 * 1. Apply 5D rotation matrix to orient space
 * 2. Extract the 3 visible dimensions
 * 3. Apply perspective projection if desired
 * 4. Hidden dimensions affect appearance (color, opacity, scale)
 */
class Projection5D {
public:
    // Projection parameters
    float hiddenDimScale;      // How much hidden dimensions affect scale
    float hiddenDimAlpha;      // How much hidden dimensions affect opacity
    bool usePerspective;       // Use perspective projection for hidden dims
    
    Projection5D()
        : hiddenDimScale(0.5f)
        , hiddenDimAlpha(0.3f)
        , usePerspective(true)
    {}

    /**
     * Project a 5D point to 3D space based on current dimension state.
     * 
     * @param point5D The 5D point to project
     * @param dimState Current dimensional viewing state
     * @return 3D coordinates in viewable space
     */
    glm::vec3 project(const Vec5D& point5D, const DimensionState& dimState) const {
        // Apply current rotation to the point
        Matrix5D rotation = dimState.getCurrentRotation();
        Vec5D rotated = rotation * point5D;
        
        // Extract the three visible dimensions
        int d0 = dimState.visibleDims[0];
        int d1 = dimState.visibleDims[1];
        int d2 = dimState.visibleDims[2];
        
        glm::vec3 result(rotated[d0], rotated[d1], rotated[d2]);
        
        // Apply effects from hidden dimensions if using perspective
        if (usePerspective) {
            float hiddenDepth = getHiddenDepth(rotated, dimState);
            float scaleFactor = 1.0f / (1.0f + hiddenDimScale * std::abs(hiddenDepth));
            result *= scaleFactor;
        }
        
        return result;
    }

    /**
     * Project multiple 5D points at once.
     */
    std::vector<glm::vec3> projectBatch(
        const std::vector<Vec5D>& points5D, 
        const DimensionState& dimState
    ) const {
        std::vector<glm::vec3> result;
        result.reserve(points5D.size());
        
        for (const auto& pt : points5D) {
            result.push_back(project(pt, dimState));
        }
        
        return result;
    }

    /**
     * Calculate opacity for a 5D object based on hidden dimensions.
     * Objects further away in hidden dimensions appear more transparent.
     */
    float calculateOpacity(const Vec5D& point5D, const DimensionState& dimState) const {
        float hiddenDepth = getHiddenDepth(point5D, dimState);
        float opacity = 1.0f - hiddenDimAlpha * (hiddenDepth / 10.0f);
        return glm::clamp(opacity, 0.1f, 1.0f);
    }

    /**
     * Calculate scale factor for a 5D object based on hidden dimensions.
     */
    float calculateScale(const Vec5D& point5D, const DimensionState& dimState) const {
        float hiddenDepth = getHiddenDepth(point5D, dimState);
        return 1.0f / (1.0f + hiddenDimScale * std::abs(hiddenDepth) * 0.1f);
    }

    /**
     * Calculate a color tint based on position in hidden dimensions.
     * This provides visual feedback about where objects are in 5D space.
     */
    glm::vec3 calculateHiddenDimTint(const Vec5D& point5D, const DimensionState& dimState) const {
        Matrix5D rotation = dimState.getCurrentRotation();
        Vec5D rotated = rotation * point5D;
        
        // Find which dimensions are hidden
        std::array<bool, 5> isVisible = {false, false, false, false, false};
        for (int vis : dimState.visibleDims) {
            isVisible[vis] = true;
        }
        
        // Use hidden dimensions to create color tint
        glm::vec3 tint(1.0f, 1.0f, 1.0f);
        float hiddenValues[2] = {0.0f, 0.0f};
        int hiddenIdx = 0;
        
        for (int i = 0; i < 5 && hiddenIdx < 2; ++i) {
            if (!isVisible[i]) {
                hiddenValues[hiddenIdx++] = rotated[i];
            }
        }
        
        // Map hidden dimensions to color channels
        // Positive values = warm colors, negative = cool colors
        if (hiddenIdx > 0) {
            float val = hiddenValues[0] * 0.1f;
            tint.r += val;
            tint.b -= val;
        }
        if (hiddenIdx > 1) {
            float val = hiddenValues[1] * 0.1f;
            tint.g += val;
        }
        
        return glm::clamp(tint, glm::vec3(0.5f), glm::vec3(1.5f));
    }

    /**
     * Check if a 5D point is "visible" (close enough in hidden dimensions).
     * Objects too far in hidden dimensions might be culled.
     */
    bool isVisible(const Vec5D& point5D, const DimensionState& dimState, float threshold = 20.0f) const {
        float hiddenDepth = getHiddenDepth(point5D, dimState);
        return std::abs(hiddenDepth) < threshold;
    }

private:
    /**
     * Calculate the "depth" in hidden dimensions.
     * This is the distance from the visible 3D slice in the remaining dimensions.
     */
    float getHiddenDepth(const Vec5D& point5D, const DimensionState& dimState) const {
        Matrix5D rotation = dimState.getCurrentRotation();
        Vec5D rotated = rotation * point5D;
        
        // Find which dimensions are hidden
        std::array<bool, 5> isVisible = {false, false, false, false, false};
        for (int vis : dimState.visibleDims) {
            isVisible[vis] = true;
        }
        
        // Calculate magnitude in hidden dimensions
        float hiddenDepthSq = 0.0f;
        for (int i = 0; i < 5; ++i) {
            if (!isVisible[i]) {
                hiddenDepthSq += rotated[i] * rotated[i];
            }
        }
        
        return std::sqrt(hiddenDepthSq);
    }
};
