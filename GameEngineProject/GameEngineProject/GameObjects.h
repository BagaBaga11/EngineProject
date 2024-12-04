#pragma once
#include <string>
#include "Sprite.h"

class Level;
class b2BodyId;
class b2ShapeId;

class GameObject : public Sprite
{
public:
    explicit GameObject(Level* mylevel);
    ~GameObject();

    void StartObject() override;
    virtual void Update(float deltaTime) override;
    void SetStartPos(float x, float y);
    void SetGravScale(float scale);
    float GetGravScale() const;
    void SetSensor(bool bullet);
    virtual void Hit();

    b2BodyId* GetBody() const;
    b2ShapeId* GetShape() const;

protected:
    Level* mylevel;
    b2BodyId* bodyID = nullptr;
    b2ShapeId* shapeID = nullptr;

    float scaleGrav = 1.0f;
    bool missile = false;
};