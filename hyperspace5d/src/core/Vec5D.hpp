#pragma once

#include <cmath>
#include <array>
#include <glm/glm.hpp>

/**
 * Vec5D - 5-Dimensional Vector Class
 * 
 * Represents a point or vector in 5D space (X, Y, Z, W, V dimensions).
 * This is the fundamental data structure for all 5D geometry operations.
 */
class Vec5D {
public:
    float x, y, z, w, v;

    // Constructors
    Vec5D() : x(0), y(0), z(0), w(0), v(0) {}
    Vec5D(float x, float y, float z, float w, float v) : x(x), y(y), z(z), w(w), v(v) {}
    Vec5D(const std::array<float, 5>& arr) : x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3]), v(arr[4]) {}

    // Array access
    float& operator[](int i) {
        switch(i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            case 4: return v;
            default: return x;
        }
    }

    const float& operator[](int i) const {
        switch(i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            case 4: return v;
            default: return x;
        }
    }

    // Vector operations
    Vec5D operator+(const Vec5D& other) const {
        return Vec5D(x + other.x, y + other.y, z + other.z, w + other.w, v + other.v);
    }

    Vec5D operator-(const Vec5D& other) const {
        return Vec5D(x - other.x, y - other.y, z - other.z, w - other.w, v - other.v);
    }

    Vec5D operator*(float scalar) const {
        return Vec5D(x * scalar, y * scalar, z * scalar, w * scalar, v * scalar);
    }

    Vec5D operator/(float scalar) const {
        return Vec5D(x / scalar, y / scalar, z / scalar, w / scalar, v / scalar);
    }

    Vec5D& operator+=(const Vec5D& other) {
        x += other.x; y += other.y; z += other.z; w += other.w; v += other.v;
        return *this;
    }

    Vec5D& operator-=(const Vec5D& other) {
        x -= other.x; y -= other.y; z -= other.z; w -= other.w; v -= other.v;
        return *this;
    }

    // Dot product
    float dot(const Vec5D& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w + v * other.v;
    }

    // Magnitude and normalization
    float magnitude() const {
        return std::sqrt(x*x + y*y + z*z + w*w + v*v);
    }

    float magnitudeSquared() const {
        return x*x + y*y + z*z + w*w + v*v;
    }

    Vec5D normalized() const {
        float mag = magnitude();
        if (mag < 1e-6f) return Vec5D();
        return *this / mag;
    }

    // Distance between two points
    float distanceTo(const Vec5D& other) const {
        return (*this - other).magnitude();
    }

    // Extract 3D slice (project onto 3 dimensions)
    glm::vec3 slice(int dim1, int dim2, int dim3) const {
        return glm::vec3((*this)[dim1], (*this)[dim2], (*this)[dim3]);
    }

    // Convert to array
    std::array<float, 5> toArray() const {
        return {x, y, z, w, v};
    }
};

// Scalar multiplication (left side)
inline Vec5D operator*(float scalar, const Vec5D& vec) {
    return vec * scalar;
}
