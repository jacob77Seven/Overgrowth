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
#include "CollisionInterface.h"

enum ECollisionType
{
    Static,
    Dynamic,
};

enum EOverlapRule
{
    Trigger,
    Hit,
};

/// \brief The game object. 
///
/// The abstract representation of an object. This class must contain public member
/// functions `move()` and `draw()` to move and draw the object, respectively.

class OObject :
    public OCommon,
    public LBaseObject,
    public ICollision
{
    //friend class OObjectManager; ///< Object manager needs access so it can manage.

protected:
    float m_fRadius = 0; ///< Bounding circle radius.
    EOverlapRule EObjectOverlapRule = EOverlapRule::Hit;
    ECollisionType EObjectCollisionType = ECollisionType::Static;
    float m_fSpeed = 0; ///< Speed.
    float m_fRotSpeed = 0; ///< Rotational speed.
    Vector2 m_vVelocity; ///< Velocity.
    bool m_bStatic = true; ///< Is static (does not move).
    bool m_bIsTarget = true; ///< Is a target.
    bool m_bIsBullet = false; ///< Is a bullet.
    void CollisionResponse(const Vector2& norm, float d, OObject* pObj) override;
    LEventTimer* m_pGunFireEvent = nullptr; ///< Gun fire event.
    BoundingBox m_BoundingBox = BoundingBox(XMFLOAT3(m_vPos.x, m_vPos.y, 0), XMFLOAT3(1, 1, 1));
    //const Vector2 GetViewVector() const; ///< Compute view vector.
    eSprite Sprite;

public:
    
    EOverlapRule GetObjectCollisionType() const { return EObjectOverlapRule; };
    ECollisionType GetObjectOverlapRule() const { return EObjectCollisionType; };
    Vector2 GetWorldLocation() const { return m_vPos; };
    const BoundingBox *GetBoundingBox() const { return &m_BoundingBox; };
    float GetRadius() const { return m_fRadius; };
    //OObject();
    //OObject(const Vector2&); ///< Constructor.
    OObject(eSprite, const Vector2&);
    OObject(const Vector2& Position);
    //virtual OObject(t, const Vector2&); ///< Constructor.
    virtual ~OObject(); ///< Destructor.

    void move(); ///< Move object.
    void draw(); ///< Draw object.
}; //OObject