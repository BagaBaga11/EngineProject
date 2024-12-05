#pragma once
#include <string>
#include "Sprite.h"


class Level;
class b2BodyId;
class b2ShapeId;
class b2WorldId;

class GameObject : public Sprite
{
public:
    explicit GameObject(Level* mylevel);
    ~GameObject();

    void StartObject() override;
    virtual void Update(float deltaTime) override;
    void SetGravScale(float scale);
    float GetGravScale() const;
    void SetSensor(bool bullet);
    virtual void Hit();

    b2BodyId* GetBody() const;
    b2ShapeId* GetShape() const;

    void GetPosition();

protected:
    Level* mylevel;
    b2BodyId* bodyID = nullptr;
    b2ShapeId* shapeID = nullptr;
    b2WorldId* worldID = nullptr;

    float Firstpos;
    float Secondpos;
    float scaleGrav = 1.0f;
    bool missile = false;
    bool vertical;
};