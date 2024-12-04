#include "GameObjects.h"
#include "Levels.h"
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"
#include <vector>
#include "Animation.h"


GameObject::GameObject(Level* mylevel) : Sprite(mylevel), mylevel(mylevel)
{
    if (mylevel) {
        mylevel->objectArray.push_back(this);
    }
}

GameObject::~GameObject()
{
    delete bodyID;
    delete shapeID;
    if (mylevel != nullptr && !mylevel->objectArray.empty())
    {
        auto itObject = std::find(mylevel->objectArray.begin(), mylevel->objectArray.end(), this);

        if (itObject != mylevel->objectArray.end())
        {
            size_t index = std::distance(mylevel->objectArray.begin(), itObject);
            mylevel->objectArray.erase(itObject);
        }
    }
}

void GameObject::StartObject()
{

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.gravityScale = GetGravScale();
    bodyDef.position = b2Vec2{ newposX,newposY };
    bodyDef.isBullet = false;
    b2BodyId* body = new b2BodyId(b2CreateBody(*mylevel->GetWorld(), &bodyDef));
    bodyID = body;
    b2Polygon dynamicBox = b2MakeBox(objSize / 4, objSize / 4);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    shapeDef.enableContactEvents = true;
    shapeID = new b2ShapeId(b2CreatePolygonShape(*bodyID, &shapeDef, &dynamicBox));
    Sprite::StartObject();
}

void GameObject::Update(float deltaTime)
{
    b2Vec2 position = b2Body_GetPosition(*bodyID);
    newposX = position.x;
    newposY = position.y;
    Sprite::Update(deltaTime);
}

void GameObject::SetStartPos(float x, float y)
{
    newposX = x;
    newposY = y;
}

void GameObject::SetGravScale(float scale)
{
    scaleGrav = scale;
}

float GameObject::GetGravScale() const
{
    return scaleGrav;
}

void GameObject::SetSensor(bool bullet)
{
    missile = bullet;
}

void GameObject::Hit()
{
    delete this;
}

b2BodyId* GameObject::GetBody() const
{
    return bodyID;
}

b2ShapeId* GameObject::GetShape() const
{
    return shapeID;
}