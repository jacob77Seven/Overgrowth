#pragma once
#include "BaseCharacter.h"

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

OBaseCharacter::OBaseCharacter(eSprite t, const Vector2& p)
    : OObject(t, p)
{
    printf("Character Created!!");
}


OBaseCharacter::OBaseCharacter(const Vector2& p)
    : OObject(p)
{
    printf("Character Created (Location only given)!!");
}


OBaseCharacter::~OBaseCharacter() {
} //destructor

/// Move object an amount that depends on its velocity and the frame time.

void OBaseCharacter::move() {
} //move

void OBaseCharacter::tick(const float dt) {

    OObject::tick(dt);
}

/// Ask the renderer to draw the sprite described in the sprite descriptor.
/// Note that `OObject` is derived from `LBaseObject` which is inherited from
/// `LSpriteDesc2D`. Therefore `LSpriteRenderer::Draw(const LSpriteDesc2D*)`
/// will accept `this` as a parameter, automatically down-casting it from
/// `OObject*` to `LSpriteDesc2D*`, effectively drawing the object from its
/// sprite descriptor.

void OBaseCharacter::draw() {
    m_pRenderer->Draw(this);
} //draw

/// Response to collision. Move back the overlap distance along the collision
/// normal. 
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to `nullptr`,
/// which means collision with a wall).

void OBaseCharacter::CollisionResponse(const Vector2& norm, float d, OObject* pObj) {
    //if (m_bDead)return; //dead, bail out

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