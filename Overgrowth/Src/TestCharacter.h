#pragma once

#include "..\GameDefines.h"
#include "BaseCharacter.h"

/// \brief The game object. 
///
/// The abstract representation of an object. This class must contain public member
/// functions `move()` and `draw()` to move and draw the object, respectively.
class TestObject;
class TestCharacter :
    public OBaseCharacter
{
protected:
    virtual void CollisionResponse(const Vector2&, float,
        OObject* = nullptr); ///< Collision response.


    //const Vector2 GetViewVector() const; ///< Compute view vector.
    eSprite Sprite;
    virtual void OnDestroy() override;
    virtual void BeginPlay() override;

public:
    TestCharacter(const Vector3& p);
    float speed;
    //OObject();
    //virtual OObject(t, const Vector2&); ///< Constructor.
    //virtual ~TestCharacter(); ///< Destructor.
    virtual void tick(const float dt) override;
}; //OObject