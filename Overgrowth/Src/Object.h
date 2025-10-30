/// \file Object.h
/// \brief Interface for the game object class OObject.

#pragma once

#include "..\GameDefines.h"
#include "Renderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"
#include "BaseObject.h"
#include "EventTimer.h"
#include "ComponentIncludes.h"
#include "CollisionInterface.h"
#include "ObjectUtilitiesInterface.h"
#include "ObjectManager.h"
#include <memory>

enum ECollisionType
{
    Static,
    Dynamic,
    None
};

enum EOverlapRule
{
    Trigger,
    Hit,
};

/// \brief The game object. 
///
/// The abstract representation of an object.

class OObject :
    public OCommon,
    public LSpriteDesc3D,
    public ICollision,
    public IObjectUtilities,
    public std::enable_shared_from_this<OObject>
{
    //friend class OObjectManager; ///< Object manager needs access so it can manage.

protected:
    float m_fRadius = 100; ///< Bounding circle radius.
    EOverlapRule EObjectOverlapRule = EOverlapRule::Hit;
    ECollisionType EObjectCollisionType = ECollisionType::Static;
    float m_fSpeed = 0; ///< Speed.
    float m_fRotSpeed = 0; ///< Rotational speed.
    Vector2 m_vVelocity; ///< Velocity.
    virtual void Collision(const Vector2& norm, float d, std::shared_ptr<OObject> pObj) override;
    LEventTimer* m_pGunFireEvent = nullptr; ///< Gun fire event.
    BoundingBox m_BoundingBox = BoundingBox(XMFLOAT3(m_vPos.x, m_vPos.y, 0), XMFLOAT3(100, 100, 100));
    //const Vector2 GetViewVector() const; ///< Compute view vector.
    bool m_bPendingDestruction = false;
    virtual void BeginPlay() override;
    virtual void OnDestroy() override;
    //OObjectManager* GetObjectManager();

public:
    void Destroy();
    bool GetPendingDestruction() { return m_bPendingDestruction; };
    ECollisionType GetObjectCollisionType() const { return EObjectCollisionType; };
    void SetObjectCollisionType(ECollisionType rule) { EObjectCollisionType = rule; };
    EOverlapRule GetObjectOverlapRule() const { return EObjectOverlapRule; };
    Vector3 GetWorldLocation() const { return m_vPos; };
    float GetRadius() const { return m_fRadius; }
    const BoundingBox *GetBoundingBox() const { return &m_BoundingBox; };
    //OObject();
    //OObject(const Vector2&); ///< Constructor.
    OObject();
    OObject(eSprite, const Vector2&);
    OObject(const Vector2& p);
    OObject(const Vector3& p);
    //virtual OObject(t, const Vector2&); ///< Constructor.
    virtual ~OObject(); ///< Destructor.
    virtual void tick(const float dt);

    void draw(); ///< Draw object.
}; //OObject