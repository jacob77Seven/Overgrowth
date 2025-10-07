/// \file Object.cpp
/// \brief Code for the game object class OObject.

#include "Object.h"
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

void OObject::tick(const float dt)
{
    m_BoundingBox.Center = XMFLOAT3(m_vPos.x, m_vPos.y, 0);
}

OObject::OObject(eSprite t, const Vector2& p)
    : LBaseObject(t, p)
{
    m_fRoll = XM_PIDIV2;
    m_bIsTarget = false;

    const float w = m_pRenderer->GetWidth(t);
    const float h = m_pRenderer->GetHeight(t);
    m_fRadius = std::max(w, h) / 2;
}

OObject::OObject(const Vector2& Position)
    : LBaseObject(Sprite, Position)
{

}

void OObject::Collision(const Vector2& norm, float d, OObject* pObj) {
    printf("Collision at distance %f\n", d);
    if (m_bDead || GetObjectCollisionType() == ECollisionType::None) 
        return; //dead or no collision, bail out
    
    const Vector2 vOverlap = d * norm; //overlap in direction of this
    const bool bStatic = !pObj || pObj->GetObjectCollisionType() == ECollisionType::Static; //whether other object is static
    
    if (GetObjectCollisionType() == ECollisionType::Dynamic && pObj->GetObjectCollisionType() == ECollisionType::Dynamic) //both objects are dynamic
        m_vPos += vOverlap / 2; //back off this object by half
    
    else if (GetObjectCollisionType() == ECollisionType::Dynamic && pObj->GetObjectCollisionType() == ECollisionType::Static) //only this object is dynamic
        m_vPos += vOverlap; //back off this object
}

//void OObject::CollisionResponse(const Vector2& norm, float d, OObject* pObj) {
//    printf("Object collision!\n");
//}
//void OObject::CollisionResponse(const Vector2& norm, float d, OObject* pObj) {

//} //CollisionResponse


//OObject::OObject()
//{
//    Vector2& p = Vector2(0, 0);
//    eSprite t = Sprite;
//    m_fRoll = XM_PIDIV2; //facing upwards
//    m_bIsTarget = false; //not a target
//
//    const float w = m_pRenderer->GetWidth(t); //sprite width
//    const float h = m_pRenderer->GetHeight(t); //sprite height
//    m_fRadius = std::max(w, h) / 2; //bounding circle radius
//} //constructor

/// Destructor.

OObject::~OObject() {
    delete m_pGunFireEvent;
} //destructor

/// Move object an amount that depends on its velocity and the frame time.

void OObject::move() {
    if (!m_bDead && !m_bStatic)
        m_vPos += m_vVelocity * m_pTimer->GetFrameTime();
} //move

/// Ask the renderer to draw the sprite described in the sprite descriptor.
/// Note that `OObject` is derived from `LBaseObject` which is inherited from
/// `LSpriteDesc2D`. Therefore `LSpriteRenderer::Draw(const LSpriteDesc2D*)`
/// will accept `this` as a parameter, automatically down-casting it from
/// `OObject*` to `LSpriteDesc2D*`, effectively drawing the object from its
/// sprite descriptor.

void OObject::draw() {
    m_pRenderer->Draw(this);
} //draw

/// Response to collision. Move back the overlap distance along the collision
/// normal. 
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to `nullptr`,
/// which means collision with a wall).

//void OObject::CollisionResponse(const Vector2& norm, float d, OObject* pObj) {
//    if (m_bDead)return; //dead, bail out
//
//    const Vector2 vOverlap = d * norm; //overlap in direction of this
//    const bool bStatic = !pObj || pObj->m_bStatic; //whether other object is static
//
//    if (!m_bStatic && !bStatic) //both objects are dynamic
//        m_vPos += vOverlap / 2; //back off this object by half
//
//    else if (!m_bStatic && bStatic) //only this object is dynamic
//        m_vPos += vOverlap; //back off this object
//} //CollisionResponse

/// Compute the view vector from the object orientation.
/// \return The view vector.

//const Vector2 OObject::GetViewVector() const {
//    return AngleToVector(m_fRoll);
//} //ViewVector