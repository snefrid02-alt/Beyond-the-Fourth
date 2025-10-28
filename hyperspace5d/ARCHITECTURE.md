# HyperSpace5D - Technical Architecture

This document explains the technical implementation details of the 5D puzzle platformer, with a focus on the mathematical foundations and rendering techniques.

## Table of Contents

1. [Mathematical Foundation](#mathematical-foundation)
2. [5D Space Representation](#5d-space-representation)
3. [Rotation Theory](#rotation-theory)
4. [Projection System](#projection-system)
5. [Physics Engine](#physics-engine)
6. [Rendering Pipeline](#rendering-pipeline)
7. [Code Organization](#code-organization)

---

## Mathematical Foundation

### Dimensional Extension

Traditional games operate in 3D space with coordinates **(x, y, z)**. HyperSpace5D extends this to 5D with coordinates **(x, y, z, w, v)**.

The key insight: **while objects exist in full 5D space, we can only visualize 3 dimensions at a time**. This creates the core gameplay mechanic - rotating your view to see different 3D "slices" of the 5D world.

### Vector Operations in 5D

All standard vector operations extend naturally to 5D:

**Addition**: 
```
(x₁, y₁, z₁, w₁, v₁) + (x₂, y₂, z₂, w₂, v₂) = (x₁+x₂, y₁+y₂, z₁+z₂, w₁+w₂, v₁+v₂)
```

**Dot Product**:
```
a · b = aₓbₓ + aᵧbᵧ + aᵩbᵩ + aᵥᵥbᵥᵥ + aᵥbᵥ
```

**Magnitude**:
```
|v| = √(x² + y² + z² + w² + v²)
```

### Implementation: Vec5D Class

```cpp
class Vec5D {
    float x, y, z, w, v;
    
    // Core operations
    Vec5D operator+(const Vec5D& other) const;
    Vec5D operator*(float scalar) const;
    float dot(const Vec5D& other) const;
    float magnitude() const;
    Vec5D normalized() const;
};
```

---

## Rotation Theory

### Rotations in Higher Dimensions

In 3D, rotations occur around axes (X, Y, or Z axis). In higher dimensions, **rotations occur in 2D planes** embedded in the higher-dimensional space.

#### Rotation Planes in 5D

With 5 dimensions, we have **C(5,2) = 10 possible rotation planes**:

1. XY plane
2. XZ plane  
3. XW plane
4. XV plane
5. YZ plane
6. YW plane
7. YV plane
8. ZW plane
9. ZV plane
10. WV plane

Each rotation plane corresponds to a simple rotation that affects only 2 coordinates while leaving the other 3 unchanged.

### 5D Rotation Matrix

A rotation by angle θ in the plane spanned by axes i and j is represented by a 5×5 matrix:

```
R_ij(θ) = 5×5 identity matrix with modifications at positions (i,i), (i,j), (j,i), (j,j):

    [i][i] =  cos(θ)
    [i][j] = -sin(θ)  
    [j][i] =  sin(θ)
    [j][i] =  cos(θ)
```

**Example**: Rotation in XW plane (axes 0 and 3):

```
⎡ cos(θ)    0    0   -sin(θ)   0 ⎤
⎢   0       1    0      0      0 ⎥
⎢   0       0    1      0      0 ⎥
⎢ sin(θ)    0    0    cos(θ)   0 ⎥
⎣   0       0    0      0      1 ⎦
```

### Composite Rotations

Complex rotations are achieved by multiplying simple rotation matrices. The order matters (matrix multiplication is not commutative):

```cpp
Matrix5D rotation = R_XY(θ₁) * R_XZ(θ₂) * R_YW(θ₃);
```

### Implementation: Matrix5D Class

```cpp
class Matrix5D {
    std::array<std::array<float, 5>, 5> m;  // Column-major storage
    
    // Create rotation in a specific plane
    static Matrix5D rotation(int axis1, int axis2, float angle);
    
    // Composite rotation from multiple angles
    static Matrix5D fromEulerAngles(
        float xy, float xz, float xw, float xv,
        float yz, float yw, float yv,
        float zw, float zv, float wv
    );
    
    // Matrix operations
    Vec5D operator*(const Vec5D& vec) const;
    Matrix5D operator*(const Matrix5D& other) const;
};
```

---

## Projection System

### The Core Challenge

We need to display 5D objects on a 2D screen. This requires two projection steps:

1. **5D → 3D**: Project from 5D space to a 3D slice
2. **3D → 2D**: Standard perspective projection to screen

### 5D to 3D Projection

At any moment, the player views 3 of the 5 dimensions. We track this with a "dimension state":

```cpp
class DimensionState {
    std::array<int, 3> visibleDims;  // Which 3 dimensions are visible
    Matrix5D rotationMatrix;          // Current 5D orientation
};
```

**Projection Process**:

1. **Rotate 5D Point**: Apply rotation matrix to transform the 5D world
   ```cpp
   Vec5D rotated = rotationMatrix * point5D;
   ```

2. **Extract 3D Slice**: Select the three visible dimensions
   ```cpp
   int d0 = visibleDims[0];
   int d1 = visibleDims[1]; 
   int d2 = visibleDims[2];
   vec3 projected = vec3(rotated[d0], rotated[d1], rotated[d2]);
   ```

3. **Apply Hidden Dimension Effects**: Use the 2 hidden dimensions to affect appearance

### Hidden Dimension Visualization

Objects have positions in dimensions we're not currently viewing. We convey this through visual effects:

#### Scale Factor

Objects farther away in hidden dimensions appear smaller:

```cpp
float hiddenDepth = sqrt(hidden_dim₁² + hidden_dim₂²);
float scale = 1.0f / (1.0f + scaleParam * hiddenDepth);
projected *= scale;
```

#### Opacity

Objects farther in hidden dimensions become more transparent:

```cpp
float opacity = 1.0f - alphaParam * (hiddenDepth / maxDistance);
opacity = clamp(opacity, 0.1f, 1.0f);
```

#### Color Tint

Position in hidden dimensions affects color:

```cpp
vec3 tint = vec3(1.0, 1.0, 1.0);
tint.r += hidden_dim₁ * colorScale;  // Red channel for 4th dimension
tint.g += hidden_dim₂ * colorScale;  // Green channel for 5th dimension
```

### Smooth Transitions

When rotating dimensions, we interpolate between views:

```cpp
Matrix5D current = getCurrentRotation() {
    if (transitioning) {
        float t = smoothstep(transitionProgress);
        return lerp(startRotation, targetRotation, t);
    }
    return rotationMatrix;
}

float smoothstep(float t) {
    return t * t * (3.0f - 2.0f * t);
}
```

---

## Physics Engine

### 5D Collision Detection

Collision detection extends AABB (Axis-Aligned Bounding Box) testing to 5 dimensions.

**Two objects collide if they overlap in ALL 5 dimensions simultaneously.**

```cpp
bool intersects5D(const GameObject5D& a, const GameObject5D& b) {
    for (int dim = 0; dim < 5; dim++) {
        float min_a = a.position[dim] - a.size[dim] * 0.5f;
        float max_a = a.position[dim] + a.size[dim] * 0.5f;
        float min_b = b.position[dim] - b.size[dim] * 0.5f;
        float max_b = b.position[dim] + b.size[dim] * 0.5f;
        
        if (max_a < min_b || max_b < min_a) {
            return false;  // No overlap in this dimension
        }
    }
    return true;  // Overlap in all 5 dimensions
}
```

### Collision Response

When resolving collisions, we identify the **minimum penetration dimension**:

```cpp
Vec5D resolveCollision(const GameObject5D& a, const GameObject5D& b) {
    float minPenetration = infinity;
    int collisionDim = 0;
    
    for (int dim = 0; dim < 5; dim++) {
        float penetration = (a.size[dim] + b.size[dim]) * 0.5f 
                          - abs(a.position[dim] - b.position[dim]);
        
        if (penetration < minPenetration) {
            minPenetration = penetration;
            collisionDim = dim;
        }
    }
    
    // Push objects apart along collision dimension
    Vec5D correction;
    correction[collisionDim] = minPenetration * sign;
    return correction;
}
```

### Movement in Current View

Player movement is restricted to the currently visible dimensions:

```cpp
void applyMovementInput(Vec5D& velocity, vec3 input, DimensionState& dims) {
    int xDim = dims.visibleDims[0];
    int yDim = dims.visibleDims[1];
    int zDim = dims.visibleDims[2];
    
    velocity[xDim] = input.x * moveSpeed;
    velocity[yDim] = input.y * jumpSpeed;  // Usually jump
    velocity[zDim] = input.z * moveSpeed;
}
```

### Gravity

Gravity acts along the "up" dimension of the current view (typically the Y dimension):

```cpp
void applyGravity(Vec5D& velocity, DimensionState& dims, float deltaTime) {
    int upDim = dims.visibleDims[1];
    velocity[upDim] -= gravityAccel * deltaTime;
}
```

---

## Rendering Pipeline

### OpenGL Rendering Flow

1. **Vertex Shader**: Transform vertices from 3D model space to screen space
2. **Fragment Shader**: Calculate lighting and color for each pixel
3. **Uniform Variables**: Pass 5D projection data to shaders

### Vertex Shader (GLSL 4.5)

```glsl
#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 uModel;      // Object transform
uniform mat4 uView;       // Camera transform  
uniform mat4 uProjection; // Perspective projection

out vec3 FragPos;
out vec3 Normal;

void main() {
    FragPos = vec3(uModel * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(uModel))) * aNormal;
    gl_Position = uProjection * uView * vec4(FragPos, 1.0);
}
```

### Fragment Shader (GLSL 4.5)

```glsl
#version 450 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 uColor;           // Base object color
uniform float uOpacity;        // Calculated from hidden dims
uniform vec3 uHiddenDimTint;   // Color tint from hidden dims

void main() {
    // Phong lighting
    vec3 ambient = 0.3 * vec3(1.0);
    
    vec3 lightDir = normalize(uLightPos - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0);
    
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = 0.5 * spec * vec3(1.0);
    
    // Combine with 5D information
    vec3 result = (ambient + diffuse + specular) * uColor * uHiddenDimTint;
    FragColor = vec4(result, uOpacity);
}
```

### Per-Object Rendering

For each game object:

```cpp
void renderObject(GameObject5D& obj, DimensionState& dimState) {
    // Project 5D position to 3D
    vec3 pos3D = projection.project(obj.position, dimState);
    
    // Extract 3D size from 5D size
    vec3 size3D = obj.size.slice(dimState.visibleDims);
    
    // Calculate visual effects from hidden dimensions
    float opacity = projection.calculateOpacity(obj.position, dimState);
    float scale = projection.calculateScale(obj.position, dimState);
    vec3 tint = projection.calculateHiddenDimTint(obj.position, dimState);
    
    // Build model matrix
    mat4 model = translate(pos3D) * scale(size3D * scale);
    
    // Set shader uniforms
    shader.setMat4("uModel", model);
    shader.setVec3("uColor", obj.color);
    shader.setFloat("uOpacity", opacity);
    shader.setVec3("uHiddenDimTint", tint);
    
    // Draw mesh
    cubeMesh.draw();
}
```

---

## Code Organization

### Module Hierarchy

```
Core Layer (Mathematics)
├── Vec5D: 5D vector operations
├── Matrix5D: 5D transformations
├── DimensionState: View state management
└── Projection5D: 5D→3D projection logic

Engine Layer (Systems)
├── GameObject5D: Base object class
├── Player5D: Player controller
├── Physics5D: Collision and physics
└── Renderer: OpenGL rendering

Game Layer (Content)
├── Level: Level interface
├── Level1, Level2, Level3: Specific levels
└── Game: Main game state and logic
```

### Key Design Patterns

#### Component Pattern
Game objects use a simple component system:
- **GameObject5D**: Base class with position, velocity, size
- **Platform5D**: Static solid object
- **MovingPlatform5D**: Animated platform
- **Goal5D**: Level completion trigger
- **Player5D**: Player with controls

#### State Pattern
Dimension viewing uses state management:
- Current visible dimensions
- Target dimensions (for transitions)
- Interpolation progress
- Smooth state transitions

#### Projection Pattern
Separation of concerns for projection:
- **DimensionState**: Tracks which dimensions are visible
- **Projection5D**: Handles mathematical projection
- **Renderer**: Applies projection and renders

### Data Flow

```
Input → Game → Player → Physics → GameObject5D positions
                                            ↓
                                    DimensionState
                                            ↓
                                      Projection5D
                                            ↓
                                        Renderer → Screen
```

---

## Performance Considerations

### Optimization Strategies

1. **Frustum Culling**: Don't render objects far in hidden dimensions
   ```cpp
   if (projection.isVisible(obj, dimState, cullingThreshold)) {
       renderObject(obj);
   }
   ```

2. **Level-of-Detail**: Reduce geometry complexity for distant objects
   
3. **Batch Rendering**: Group objects by shader and material

4. **Spatial Partitioning**: Use 5D octrees (actually 32-trees!) for efficient collision queries

### Memory Layout

- Use cache-friendly data structures
- Store 5D vectors as contiguous arrays of floats
- Column-major matrices for OpenGL compatibility

---

## Future Architectural Improvements

### Quaternion-like Interpolation

Current dimension transitions use linear matrix interpolation. A better approach would use **rotors** (geometric algebra) or **5D quaternion equivalents** for smoother, shorter-path rotations.

### Procedural Generation

5D space allows for fascinating procedural generation:
- Hypercube-based dungeons
- Fractal 5D structures
- Topologically interesting mazes

### Advanced Rendering

- **Hyperbolic Space**: Combine with non-Euclidean geometry
- **Ray Marching**: Direct 5D→2D ray marching for complex shapes
- **Compute Shaders**: GPU-accelerated 5D transformations

---

## Conclusion

HyperSpace5D demonstrates that higher-dimensional games are not only possible but create genuinely novel gameplay mechanics. The key is providing intuitive visual feedback about hidden dimensions through color, opacity, and scale.

The mathematical foundation (5D vectors, matrices, rotations) extends naturally from 3D graphics programming. The main challenge is designing levels that teach players to "think in 5D" through progressive puzzle difficulty.

**Welcome to the fifth dimension!** 🚀
