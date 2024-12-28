#include "Sprite.h"
#include "SDL.h"
#include "GameEngineProject.h"
#include "Levels.h"
#include "glad\glad.h"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
using namespace glm;
Sprite::Sprite(Level* mylevel) : mylevel(mylevel)
{
    if (mylevel) {
        mylevel->everyArray.push_back(this);
    }
    modelMatrix = new glm::mat4;
    texture = new GLuint;
}
Sprite::~Sprite() {
    objRect = nullptr;

    objPosition = nullptr;

    delete(texture);
    delete(modelMatrix);

        auto itObject = std::find(mylevel->everyArray.begin(), mylevel->everyArray.end(), this);

        if (itObject != mylevel->everyArray.end())
        {
            size_t index = std::distance(mylevel->everyArray.begin(), itObject);
            mylevel->everyArray.erase(itObject);

            if (index < mylevel->bmpArray.size())
            {
                mylevel->bmpArray.erase(mylevel->bmpArray.begin() + index);
            }
        } 
}

void Sprite::SetBMP(const std::string& image, int wSec, int hSec, int objsize)
{
    myBMP = image;
    widthSection = wSec;
    heightSection = hSec;
    objSize = objsize;
}

void Sprite::Update(float deltaTime)
{
    objPosition->x = newposX;
    objPosition->y = newposY;
    objPosition->h = objSize;
    objPosition->w = objSize;
    animationManager.Update(deltaTime);

    int frameIndex = animationManager.GetCurrentFrame();
    objRect->x = (frameIndex % widthSection) * frameWidth;
    objRect->y = (frameIndex / widthSection) * frameHeight;
}

void Sprite::StartObject()
{
    texture = LoadTexture(myBMP);
    if (widthSection != 0 && heightSection != 0) {
        frameWidth = textureWidth / widthSection;
        frameHeight = textureHeight / heightSection;
    }
    objRect = new SDL_Rect{ 0, 0, frameWidth, frameHeight };
    objPosition = new SDL_Rect;
    mylevel->bmpArray.push_back(texture);
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

void Sprite::Draw(GLuint shadrProg, GLuint vao)
{
    glUseProgram(shadrProg);
    glBindVertexArray(vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *texture);

    GLuint modelLoc = glGetUniformLocation(shadrProg, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(*modelMatrix));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::SetTransform(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis)
{
    *modelMatrix = glm::mat4(1.0f);
    *modelMatrix = glm::translate(*modelMatrix, position);
    *modelMatrix = glm::scale(*modelMatrix, scale);
    *modelMatrix = glm::rotate(*modelMatrix, glm::radians(rotationAngle), rotationAxis);
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

GLuint* Sprite::LoadTexture(std::string filePath)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture: " << filePath << std::endl;
    }
    stbi_image_free(data);

    return texture;
}