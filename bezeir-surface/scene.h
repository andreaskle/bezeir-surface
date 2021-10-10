#ifndef SCENE_H
#define SCENE_H
#include <iostream>

#include "camera.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

class Scene {
   public:
    ~Scene();
    void Init(int width, int height);
    void Render(float dt);

    void ToggleWireframe();
    void IncreaseTessFactor() {
        tessFactor++;
        tessFactor = std::min(tessFactor, 6.0f);
    }
    void DecreaseTessFactor() {
        tessFactor--;
        tessFactor = std::max(tessFactor, 0.0f);
    }

   private:
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
    GLuint tessellationControlShader = 0;
    GLuint tessellationEvaluationShader = 0;
    GLuint shaderProgram = 0;
    GLuint vertexBuffer = 0;
    GLuint indexBuffer = 0;
    GLuint vertexArrayObject = 0;

    Camera camera;
    float tessFactor = 0;
    bool wireFrame = false;
};
#endif
