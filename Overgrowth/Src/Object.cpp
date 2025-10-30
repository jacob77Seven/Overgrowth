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
{
    printf("Called OObject(eSprite t, const Vector2& p)\n");

    m_vPos.x = p.x;
    m_vPos.y = p.y;
    m_fRoll = XM_PIDIV2;
}

OObject::OObject(const Vector2& p)
{

    printf("Called OObject(const Vector2& p)\n");
    m_vPos.x = p.x;
    m_vPos.y = p.y;
    m_fRoll = XM_PIDIV2;
}

OObject::OObject()
{
    printf("Called OObject()\n");
    //m_vPos.x = 500;
    //m_vPos.y = 0;
    m_fRoll = XM_PIDIV2;
}

OObject::OObject(const Vector3& p)
{
    printf("Called OObject(const Vector3 - %f, %f, %f)\n", p.x, p.y, p.z);
    m_vPos.x = p.x;
    m_vPos.y = p.y;
    m_vPos.z = p.z;
    printf("OObject has become -  %f, %f, %f\n", m_vPos.x, m_vPos.y, m_vPos.z);
}

void OObject::BeginPlay() {
    m_BoundingBox = BoundingBox(XMFLOAT3(m_vPos.x, m_vPos.y, 0), XMFLOAT3(100, 100, 100));
    printf("Object BeginPlay!\n");
}

void OObject::OnDestroy()
{
    printf("Object Being Destroyed.\n");
}

void OObject::Destroy()
{
    m_bPendingDestruction = true;
}

void OObject::Collision(const Vector2& norm, float d, std::shared_ptr<OObject> pObj) {
    printf("Collision at distance %f\n", d);
    if (m_bPendingDestruction || GetObjectCollisionType() == ECollisionType::None) 
        return; //dead or no collision, bail out
    
    const Vector2 vOverlap = d * norm; //overlap in direction of this
    const bool bStatic = !pObj || pObj->GetObjectCollisionType() == ECollisionType::Static; //whether other object is static
    
    if (GetObjectCollisionType() == ECollisionType::Dynamic && pObj->GetObjectCollisionType() == ECollisionType::Dynamic) { //both objects are dynamic
        m_vPos.x += vOverlap.x / 2; //back off this object by half
        m_vPos.y += vOverlap.y / 2; //back off this object by half
    }
    
    else if (GetObjectCollisionType() == ECollisionType::Dynamic && pObj->GetObjectCollisionType() == ECollisionType::Static) { //only this object is dynamic
        m_vPos.x += vOverlap.x; //back off this object by half
        m_vPos.y += vOverlap.y; //back off this object by half
    }
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
    //printf("Object destructor called.\n");
} //destructor

/// Ask the renderer to draw the sprite described in the sprite descriptor.
/// Note that `OObject` is derived from `LBaseObject` which is inherited from
/// `LSpriteDesc2D`. Therefore `LSpriteRenderer::Draw(const LSpriteDesc2D*)`
/// will accept `this` as a parameter, automatically down-casting it from
/// `OObject*` to `LSpriteDesc2D*`, effectively drawing the object from its
/// sprite descriptor.

void OObject::draw() {
    m_pRenderer->Draw(this);
    //m_pRenderer->DrawBoundingBox(eSprite::PinkSquare, m_BoundingBox);
    //printf("bb xyz - %f %f %f\n", m_BoundingBox.Center.x, m_BoundingBox.Center.y, m_BoundingBox.Center.z);
    //printf("bb xyz - %f %f %f\n", m_BoundingBox.Extents.x, m_BoundingBox.Extents.y, m_BoundingBox.Extents.z);
} //draw

/// Response to collision. Move back the overlap distance along the collision
/// normal. 
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to `nullptr`,
/// which means collision with a wall).

//void OObject::CollisionResponse(const Vector2& norm, float d, OObject* pObj) {
//    if (m_bPendingDestruction)return; //dead, bail out
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