#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "../core/Projection5D.hpp"
#include "GameObject5D.hpp"

/**
 * Shader - Manages OpenGL shader programs
 */
class Shader {
public:
    GLuint ID;

    Shader() : ID(0) {}

    bool load(const std::string& vertexPath, const std::string& fragmentPath) {
        std::string vertexCode = readFile(vertexPath);
        std::string fragmentCode = readFile(fragmentPath);
        
        if (vertexCode.empty() || fragmentCode.empty()) {
            return false;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        GLuint vertex, fragment;
        
        // Compile vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        if (!checkCompileErrors(vertex, "VERTEX")) {
            return false;
        }

        // Compile fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        if (!checkCompileErrors(fragment, "FRAGMENT")) {
            glDeleteShader(vertex);
            return false;
        }

        // Link shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        if (!checkCompileErrors(ID, "PROGRAM")) {
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            return false;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
        return true;
    }

    void use() const {
        glUseProgram(ID);
    }

    void setMat4(const std::string& name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setVec3(const std::string& name, const glm::vec3& vec) const {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
    }

    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

private:
    std::string readFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open shader file: " << path << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    bool checkCompileErrors(GLuint shader, const std::string& type) {
        GLint success;
        GLchar infoLog[1024];
        
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "Shader compilation error (" << type << "): " << infoLog << std::endl;
                return false;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "Program linking error: " << infoLog << std::endl;
                return false;
            }
        }
        return true;
    }
};

/**
 * Mesh - Simple cube mesh for rendering
 */
class Mesh {
public:
    GLuint VAO, VBO;

    Mesh() : VAO(0), VBO(0) {}

    ~Mesh() {
        if (VAO) glDeleteVertexArrays(1, &VAO);
        if (VBO) glDeleteBuffers(1, &VBO);
    }

    void createCube() {
        // Cube vertices with normals
        float vertices[] = {
            // positions          // normals
            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            // Left face
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            // Right face
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            // Bottom face
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            // Top face
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void draw() const {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
};

/**
 * Renderer - Handles 3D rendering of 5D objects
 */
class Renderer {
public:
    Shader shader;
    Mesh cubeMesh;
    Projection5D projection;
    glm::vec3 cameraPos;
    glm::vec3 lightPos;

    Renderer() : cameraPos(0.0f, 5.0f, 15.0f), lightPos(10.0f, 10.0f, 10.0f) {}

    bool initialize() {
        if (!shader.load("shaders/vertex.glsl", "shaders/fragment.glsl")) {
            std::cerr << "Failed to load shaders" << std::endl;
            return false;
        }

        cubeMesh.createCube();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return true;
    }

    void renderObject(const GameObject5D& obj, const DimensionState& dimState,
                     const glm::mat4& view, const glm::mat4& projection) {
        
        if (!obj.isVisible) return;

        // Project 5D position to 3D
        glm::vec3 pos3D = this->projection.project(obj.position, dimState);
        glm::vec3 size3D = obj.size.slice(
            dimState.visibleDims[0],
            dimState.visibleDims[1],
            dimState.visibleDims[2]
        );

        // Calculate scale based on hidden dimensions
        float hiddenScale = this->projection.calculateScale(obj.position, dimState);
        size3D *= hiddenScale;

        // Calculate opacity
        float opacity = obj.opacity * this->projection.calculateOpacity(obj.position, dimState);

        // Calculate color tint from hidden dimensions
        glm::vec3 tint = this->projection.calculateHiddenDimTint(obj.position, dimState);

        // Create model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos3D);
        model = glm::scale(model, size3D);

        // Set uniforms
        shader.use();
        shader.setMat4("uModel", model);
        shader.setMat4("uView", view);
        shader.setMat4("uProjection", projection);
        shader.setVec3("uColor", obj.color);
        shader.setFloat("uOpacity", opacity);
        shader.setVec3("uLightPos", lightPos);
        shader.setVec3("uViewPos", cameraPos);
        shader.setVec3("uHiddenDimTint", tint);

        cubeMesh.draw();
    }

    void renderScene(const std::vector<std::shared_ptr<GameObject5D>>& objects,
                    const DimensionState& dimState,
                    int screenWidth, int screenHeight) {
        
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Create view and projection matrices
        glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 
                                          (float)screenWidth / (float)screenHeight,
                                          0.1f, 100.0f);

        // Render all objects
        for (const auto& obj : objects) {
            renderObject(*obj, dimState, view, proj);
        }
    }
};
