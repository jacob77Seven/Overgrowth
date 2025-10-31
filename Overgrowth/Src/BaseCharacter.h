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

    virtual void CollisionResponse(const Vector2& norm, float d, std::weak_ptr<OObject> pObj); ///< Collision response.

    //const Vector2 GetViewVector() const; ///< Compute view vector.
    eSprite Sprite;
    virtual void OnDestroy() override;
    virtual void BeginPlay() override;

public:
    OBaseCharacter(const Vector3& p);
    //OObject();
    //virtual OObject(t, const Vector2&); ///< Constructor.
    virtual ~OBaseCharacter(); ///< Destructor.
    virtual void tick(const float dt) override;
    //void draw(); ///< Draw object.
}; //OObject