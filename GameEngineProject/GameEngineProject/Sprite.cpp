#include "Sprite.h"
#include "SDL.h"
#include "GameEngineProject.h"
#include "Levels.h"
#include "glad\glad.h"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <memory>
#include "stb_image.h"

struct Transform::Impl {
    glm::vec3 position;
    glm::vec3 scale;
    glm::mat4 modelMatrix;
    GLuint ebo;
    GLuint vbo;
    GLuint vao;
    GLuint shaderProgram;
    GLuint texture;
};

Transform::Transform() : pImpl(std::make_unique<Impl>()) {
    pImpl->position = glm::vec3(0.0f);
    pImpl->scale = glm::vec3(1.0f);
    pImpl->modelMatrix = glm::mat4(1.0f);
}

Transform::~Transform()
{
    if (pImpl->vao) glDeleteVertexArrays(1, &pImpl->vao);
    if (pImpl->vbo) glDeleteBuffers(1, &pImpl->vbo);
    if (pImpl->ebo) glDeleteBuffers(1, &pImpl->ebo);
    if (pImpl->shaderProgram) glDeleteProgram(pImpl->shaderProgram);
}

void Transform::SetPosition(float x, float y, float z) {
    pImpl->position = glm::vec3(x, y, z);
    pImpl->modelMatrix = glm::translate(glm::mat4(1.0f), pImpl->position);
}

void Transform::SetScale(float x, float y, float z) {
    pImpl->scale = glm::vec3(x, y, z);
    pImpl->modelMatrix = glm::scale(glm::mat4(1.0f), pImpl->scale);
}

void Transform::SetRotation(float angle, float x, float y, float z) {
    pImpl->modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(x, y, z));
}

void Transform::Draw()
{
    glUseProgram(pImpl->shaderProgram);
    glBindVertexArray(pImpl->vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pImpl->texture);

    GLuint modelLoc = glGetUniformLocation(pImpl->shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pImpl->modelMatrix));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
void Transform::Start()
{

    float vertices[] = {
        // positions          // colors
         0.1f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f, // top right
         0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom right
        -0.1f, -0.1f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
        -0.1f,  0.1f, 0.0f,   1.0f, 1.0f, 0.0f  // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &pImpl->vao);
    glGenBuffers(1, &pImpl->vbo);
    glGenBuffers(1, &pImpl->ebo);

    glBindVertexArray(pImpl->vao);


    glBindBuffer(GL_ARRAY_BUFFER, pImpl->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pImpl->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const char* vertexShaderSource = R"glsl(
        #version 330 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 color;

        out vec3 Color;

        uniform mat4 model;

        void main() {
            Color = color;
            gl_Position = model * vec4(position, 1.0);
        }
    )glsl";

    const char* fragmentShaderSource = R"glsl(
        #version 330 core
        in vec3 Color;

        out vec4 FragColor;

        void main() {
            FragColor = vec4(Color, 1.0);
        }
    )glsl";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    pImpl->shaderProgram = glCreateProgram();
    glAttachShader(pImpl->shaderProgram, vertexShader);
    glAttachShader(pImpl->shaderProgram, fragmentShader);
    glLinkProgram(pImpl->shaderProgram);

    glGetProgramiv(pImpl->shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(pImpl->shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);  
}

void Transform::SetTexture(const char* image, float Ncol,float Nlin, float size)
{
    glGenTextures(1, &pImpl->texture);
    glBindTexture(GL_TEXTURE_2D, pImpl->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(image, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    GLuint texCoordStartLocation = glGetUniformLocation(pImpl->shaderProgram, "texCoordStart");
    GLuint texCoordEndLocation = glGetUniformLocation(pImpl->shaderProgram, "texCoordEnd");
    GLuint scaleFactorLocation = glGetUniformLocation(pImpl->shaderProgram, "scaleFactor");

    glUseProgram(pImpl->shaderProgram);
    glUniform1f(scaleFactorLocation, size);


    float x1 = 1.0 / (2 * Ncol);
    float x2 = x1 + 2.0 / (2 * Ncol);  
    float y1 = ((2 * Nlin) + 1) / (2 * Nlin);  
    float y2 = y1 - (2 / (2 * Nlin));  

    GLuint textureLocation;
    GLuint textureLocation2;

    glUniform2f(texCoordStartLocation, x1, y2); 
    glUniform2f(texCoordEndLocation, x2, y1);  


    textureLocation = glGetUniformLocation(pImpl->shaderProgram, "ourTexture");

    glUniform1i(textureLocation, 0);

    glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
}

Sprite::Sprite(Level* mylevel) : mylevel(mylevel)
{
    t = new Transform;
    if (mylevel) {
        mylevel->everyArray.push_back(this);
    }
}
Sprite::~Sprite() {
    objRect = nullptr;

    objPosition = nullptr;


        auto itObject = std::find(mylevel->everyArray.begin(), mylevel->everyArray.end(), this);

        if (itObject != mylevel->everyArray.end())
        {
            size_t index = std::distance(mylevel->everyArray.begin(), itObject);
            mylevel->everyArray.erase(itObject);

           /* if (index < mylevel->bmpArray.size())
            {
                mylevel->bmpArray.erase(mylevel->bmpArray.begin() + index);
            }*/
        } 
        delete(t);
}

void Sprite::SetBMP(const std::string& image, int wSec, int hSec, int objsize)
{
    objSize = objsize;
    t->SetTexture(image.c_str(), wSec, hSec, 20);
}

void Sprite::Update(float deltaTime)
{
    t->Draw();
    animationManager.Update(deltaTime);

    int frameIndex = animationManager.GetCurrentFrame();
}

void Sprite::StartObject()
{
    t->Start();
    if (widthSection != 0 && heightSection != 0) {
        frameWidth = textureWidth / widthSection;
        frameHeight = textureHeight / heightSection;
    }
    objRect = new SDL_Rect{ 0, 0, frameWidth, frameHeight };
    objPosition = new SDL_Rect;
    //mylevel->bmpArray.push_back(texture);
}

SDL_Rect* Sprite::GetRect() const
{
    return objRect;
}

void Sprite::SetStartPos(float x, float y)
{
    newposX = x;
    newposY = y;
}

void Sprite::SetRotation(double angle,SDL_Point pivot)
{
    rotationAngle = angle;
    rotationPivot = new SDL_Point(pivot);
}

void Sprite::Draw()
{
}

SDL_Point* Sprite::GetPivot()
{
    if (rotationPivot)
    {
         return rotationPivot;
    }
    return 0;
}

double Sprite::GetAngle()
{
    return rotationAngle;
}
