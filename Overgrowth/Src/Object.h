/// \file Object.h
/// \brief Interface for the game object class OObject.

#pragma once

#include "..\GameDefines.h"
#include "SpriteRenderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"
#include "BaseObject.h"
#include "EventTimer.h"
#include "ComponentIncludes.h"

/// \brief The game object. 
///
/// The abstract representation of an object. This class must contain public member
/// functions `move()` and `draw()` to move and draw the object, respectively.

class OObject :
    public OCommon,
    public LBaseObject
{
    //friend class OObjectManager; ///< Object manager needs access so it can manage.

protected:
    float m_fRadius = 0; ///< Bounding circle radius.

    float m_fSpeed = 0; ///< Speed.
    float m_fRotSpeed = 0; ///< Rotational speed.
    Vector2 m_vVelocity; ///< Velocity.
    bool m_bStatic = true; ///< Is static (does not move).
    bool m_bIsTarget = true; ///< Is a target.
    bool m_bIsBullet = false; ///< Is a bullet.

    LEventTimer* m_pGunFireEvent = nullptr; ///< Gun fire event.

    virtual void CollisionResponse(const Vector2&, float,
        OObject* = nullptr); ///< Collision response.

    //const Vector2 GetViewVector() const; ///< Compute view vector.
    eSprite Sprite;

public:
    //OObject();
    //OObject(const Vector2&); ///< Constructor.
    OObject(eSprite, const Vector2&);
    OObject(const Vector2& Position);
    //virtual OObject(t, const Vector2&); ///< Constructor.
    virtual ~OObject(); ///< Destructor.

    void move(); ///< Move object.
    void draw(); ///< Draw object.
}; //OObject