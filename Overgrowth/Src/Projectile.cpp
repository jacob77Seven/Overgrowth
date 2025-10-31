#pragma once
#include "Projectile.h"
#include "TestCharacter.h"
/// \file Object.cpp
/// \brief Code for the game object class OBaseCharacter

#include "ComponentIncludes.h"
#include "../GameDefines.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "Helpers.h"

/// Create and initialize an object given its sprite type and initial position.
/// \param t Type of sprite.
/// \param p Initial position of object.

//OObject::OObject(const Vector2& p)
//{
//    eSprite t = Sprite;
//    m_fRoll = XM_PIDIV2; //facing upwards
//    m_bIsTarget = false; //not a target
//
//    const float w = m_pRenderer->GetWidth(t); //sprite width
//    const float h = m_pRenderer->GetHeight(t); //sprite height
//    m_fRadius = std::max(w, h) / 2; //bounding circle radius
//} //constructor

void Projectile::BeginPlay()
{
    OObject::BeginPlay(); // Call to parent class.
    printf("Character Begin Play!");
}

Projectile::Projectile(const Vector3& p)
    : OObject(p)
{
    m_fSpeed = 420.f;
    m_nSpriteIndex = (UINT)eSprite::walkright;
    EObjectCollisionType = ECollisionType::Dynamic;
    printf("OBaseCharacter has become -  %f, %f, %f\n", m_vPos.x, m_vPos.y, m_vPos.z);
}

//Projectile::~Projectile() {
//    OObject::~OObject(); // Call to parent destructor.
//} //destructor


void Projectile::OnDestroy() {
    OObject::OnDestroy();
    printf("Test object has been Destroyed.\n");
}

void Projectile::tick(const float dt) {
    m_vPos.x += dt * m_fSpeed;
    OObject::tick(dt);
}

/// Ask the renderer to draw the sprite described in the sprite descriptor.
/// Note that `OObject` is derived from `LBaseObject` which is inherited from
/// `LSpriteDesc2D`. Therefore `LSpriteRenderer::Draw(const LSpriteDesc2D*)`
/// will accept `this` as a parameter, automatically down-casting it from
/// `OObject*` to `LSpriteDesc2D*`, effectively drawing the object from its
/// sprite descriptor.

void Projectile::draw() {
    m_pRenderer->Draw(this);
} //draw

/// Response to collision. Move back the overlap distance along the collision
/// normal. 
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to `nullptr`,
/// which means collision with a wall).

void Projectile::CollisionResponse(const Vector2& norm, float d, std::weak_ptr<OObject> pObj) {
    if (auto o = pObj.lock()) {
        if (auto character = std::dynamic_pointer_cast<TestCharacter>(o)) {
            //character->Destroy();
        }
    }
    // CollisionResponse(const Vector2& norm, float d, std::weak_ptr<OObject> pObj)
    //if (m_bPendingDestruction)return; //dead, bail out

    //const Vector2 vOverlap = d * norm; //overlap in direction of this
    //const bool bStatic = !pObj || pObj->m_bStatic; //whether other object is static

    //if (!m_bStatic && !bStatic) //both objects are dynamic
    //    m_vPos += vOverlap / 2; //back off this object by half

    //else if (!m_bStatic && bStatic) //only this object is dynamic
    //    m_vPos += vOverlap; //back off this object
} //CollisionResponse

/// Compute the view vector from the object orientation.
/// \return The view vector.

//const Vector2 OObject::GetViewVector() const {
//    return AngleToVector(m_fRoll);
//} //ViewVector