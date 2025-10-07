#pragma once

#include "..\GameDefines.h"
#include "BaseCharacter.h"

/// \brief The game object. 
///
/// The abstract representation of an object. This class must contain public member
/// functions `move()` and `draw()` to move and draw the object, respectively.

class TestCharacter :
    public OBaseCharacter
{
protected:
    virtual void CollisionResponse(const Vector2&, float,
        OObject* = nullptr); ///< Collision response.

    //const Vector2 GetViewVector() const; ///< Compute view vector.
    eSprite Sprite;
public:
    float speed = 180.f;
    //OObject();
    TestCharacter(const Vector2& p); ///< Constructor.
    TestCharacter(eSprite, const Vector2&);
    //virtual OObject(t, const Vector2&); ///< Constructor.
    virtual ~TestCharacter(); ///< Destructor.
    virtual void tick(const float dt) override;

    void move(); ///< Move object.
    void draw(); ///< Draw object.
}; //OObject