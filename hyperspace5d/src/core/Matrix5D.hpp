#pragma once

#include "Vec5D.hpp"
#include <array>
#include <cmath>

/**
 * Matrix5D - 5x5 Matrix for 5D transformations
 * 
 * Represents linear transformations in 5D space, including rotations,
 * scaling, and other affine transformations.
 * 
 * Matrix layout is column-major to match OpenGL conventions.
 */
class Matrix5D {
public:
    // Data stored in column-major order: m[column][row]
    std::array<std::array<float, 5>, 5> m;

    // Constructors
    Matrix5D() {
        identity();
    }

    // Create identity matrix
    void identity() {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                m[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }

    // Matrix-vector multiplication
    Vec5D operator*(const Vec5D& vec) const {
        Vec5D result;
        for (int row = 0; row < 5; ++row) {
            result[row] = 0;
            for (int col = 0; col < 5; ++col) {
                result[row] += m[col][row] * vec[col];
            }
        }
        return result;
    }

    // Matrix-matrix multiplication
    Matrix5D operator*(const Matrix5D& other) const {
        Matrix5D result;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                result.m[i][j] = 0;
                for (int k = 0; k < 5; ++k) {
                    result.m[i][j] += m[k][j] * other.m[i][k];
                }
            }
        }
        return result;
    }

    /**
     * Create a 5D rotation matrix in the plane defined by two axes.
     * 
     * In 5D space, rotations occur in 2D planes embedded in the 5D space.
     * This creates a rotation of 'angle' radians in the plane spanned by
     * dimensions axis1 and axis2, leaving other dimensions unchanged.
     * 
     * @param axis1 First axis (0-4 for X,Y,Z,W,V)
     * @param axis2 Second axis (0-4 for X,Y,Z,W,V)
     * @param angle Rotation angle in radians
     * @return Rotation matrix
     */
    static Matrix5D rotation(int axis1, int axis2, float angle) {
        Matrix5D mat;
        
        float c = std::cos(angle);
        float s = std::sin(angle);
        
        // Start with identity
        mat.identity();
        
        // Apply rotation in the specified plane
        mat.m[axis1][axis1] = c;
        mat.m[axis2][axis1] = s;
        mat.m[axis1][axis2] = -s;
        mat.m[axis2][axis2] = c;
        
        return mat;
    }

    /**
     * Create a composite rotation matrix from Euler-like angles.
     * 
     * 5D rotations can be decomposed into 10 planar rotations (one for each
     * pair of axes). This creates a rotation matrix from angles in each plane.
     * 
     * Planes: XY, XZ, XW, XV, YZ, YW, YV, ZW, ZV, WV
     */
    static Matrix5D fromEulerAngles(
        float xy, float xz, float xw, float xv,
        float yz, float yw, float yv,
        float zw, float zv,
        float wv
    ) {
        Matrix5D result;
        
        // Apply rotations in sequence
        // Order matters! This is similar to Euler angles in 3D
        result = rotation(0, 1, xy) *  // XY plane
                 rotation(0, 2, xz) *  // XZ plane
                 rotation(0, 3, xw) *  // XW plane
                 rotation(0, 4, xv) *  // XV plane
                 rotation(1, 2, yz) *  // YZ plane
                 rotation(1, 3, yw) *  // YW plane
                 rotation(1, 4, yv) *  // YV plane
                 rotation(2, 3, zw) *  // ZW plane
                 rotation(2, 4, zv) *  // ZV plane
                 rotation(3, 4, wv);   // WV plane
        
        return result;
    }

    // Transpose
    Matrix5D transpose() const {
        Matrix5D result;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                result.m[i][j] = m[j][i];
            }
        }
        return result;
    }

    // Get a specific element
    float& at(int col, int row) {
        return m[col][row];
    }

    const float& at(int col, int row) const {
        return m[col][row];
    }
};
