#include "scene.h"

#include "glm/gtc/type_ptr.hpp"
#include "opengl/utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
struct Vertex {
    glm::vec3 pos;
};

Scene::~Scene() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(tessellationEvaluationShader);
    glDeleteShader(tessellationControlShader);
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteVertexArrays(1, &vertexArrayObject);
}
void Scene::Init(int width, int height) {
    vertexShader = CreateShaderFromFile(GL_VERTEX_SHADER, "bezeir-surface/shaders/vertex.glsl");
    fragmentShader = CreateShaderFromFile(GL_FRAGMENT_SHADER, "bezeir-surface/shaders/fragment.glsl");
    tessellationControlShader = CreateShaderFromFile(GL_TESS_CONTROL_SHADER, "bezeir-surface/shaders/tesscontrol.glsl");
    tessellationEvaluationShader =
        CreateShaderFromFile(GL_TESS_EVALUATION_SHADER, "bezeir-surface/shaders/tesseval.glsl");
    shaderProgram = CreateProgram({vertexShader, fragmentShader, tessellationEvaluationShader});

    Vertex vertices[] = {{glm::vec3(-1, -1, 0)}, {glm::vec3(1, -1, 0)}, {glm::vec3(1, 1, 0)}, {glm::vec3(-1, 1, 0)}};

    // Create Vertex Buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, vertices, GL_STATIC_DRAW);

    // Create Vertex Array Object
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    // enable first vertex attrib (position)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
    glBindVertexArray(0);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    camera.Perspective(width, height);
    glPatchParameteri(GL_PATCH_VERTICES, 4);
}

void Scene::Render(float dt) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float tess_levels[4] = {std::pow(2.0f, tessFactor), std::pow(2.0f, tessFactor), std::pow(2.0f, tessFactor),
                            std::pow(2.0f, tessFactor)};
    glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, tess_levels);
    glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, tess_levels);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glUseProgram(shaderProgram);

    glm::mat4 mvpMatrix = camera.GetViewProjMatrix();
    glm::vec3 eyeVec = -glm::normalize(camera.GetPosition());
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewProj"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));
    glUniform3f(glGetUniformLocation(shaderProgram, "eyeVec"), eyeVec.x, eyeVec.y, eyeVec.z);
    glUniform1i(glGetUniformLocation(shaderProgram, "tessellationFactor"), pow(2, tessFactor));
    glDrawArrays(GL_PATCHES, 0, 4);
    glUseProgram(0);

    glBindVertexArray(0);
}

void Scene::ToggleWireframe() {
    wireFrame = !wireFrame;
    glPolygonMode(GL_FRONT_AND_BACK, wireFrame ? GL_LINE : GL_FILL);
}