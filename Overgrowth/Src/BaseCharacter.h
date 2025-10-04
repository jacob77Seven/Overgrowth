/// \file Object.h
/// \brief Interface for the game object class OObject.

#pragma once

#include "..\GameDefines.h"
#include "SpriteRenderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"
#include "Object.h"
#include "EventTimer.h"
#include "ComponentIncludes.h"

/// \brief The game object. 
///
/// The abstract representation of an object. This class must contain public member
/// functions `move()` and `draw()` to move and draw the object, respectively.

class OBaseCharacter :
    public OObject
{
protected:
    float m_fRadius = 0; ///< Bounding circle radius.

    float m_fSpeed = 0; ///< Speed.

    virtual void CollisionResponse(const Vector2&, float,
        OObject* = nullptr); ///< Collision response.

    //const Vector2 GetViewVector() const; ///< Compute view vector.
    eSprite Sprite;

public:
    //OObject();
    OBaseCharacter(const Vector2& p); ///< Constructor.
    OBaseCharacter(eSprite, const Vector2&);
    //virtual OObject(t, const Vector2&); ///< Constructor.
    virtual ~OBaseCharacter(); ///< Destructor.

    void move(); ///< Move object.
    void draw(); ///< Draw object.
}; //OObject