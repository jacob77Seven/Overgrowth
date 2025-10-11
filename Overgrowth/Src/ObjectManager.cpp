/// \file ObjectManager.cpp
/// \brief Code for the the object manager class OObjectManager.

#include "ObjectManager.h"
#include "ComponentIncludes.h"

#include "ParticleEngine.h"
#include "Helpers.h"
#include "../GameDefines.h"
//#include "TileManager.h"

#include <iostream>
#include <type_traits>

std::vector<std::shared_ptr<OObject>> OObjectManager::OObjectList;


void OObjectManager::draw(){
    //m_pTileManager->Draw(eSprite::Tile); //draw tiled background
    
    // if(m_bDrawAABBs)
    //     m_pTileManager->DrawBoundingBoxes(eSprite::Line); //draw AABBs

    for (std::shared_ptr<OObject> pObj : OObjectList){ //for each object
        //pObj->draw();
        if (m_pRenderer && pObj)
            //m_pRenderer->DrawBoundingBox(10, *pObj->GetBoundingBox());
            m_pRenderer->DrawBoundingBox(eSprite::PinkSquare, *pObj->GetBoundingBox());
            //m_pRenderer->DrawBoundingBox(12, BoundingBox(XMFLOAT3(m_vWinCenter.x, m_vWinCenter.y,0), XMFLOAT3(100, 100, 100)));
            m_pRenderer->Draw(eSprite::Pig, pObj->GetWorldLocation());
    } //for
        //m_pRenderer->DrawBoundingBox(1, BoundingBox(XMFLOAT3(0, 0, 0), XMFLOAT3(500, 500, 500)));

    // LBaseObjectManager::draw();
} //draw

void OObjectManager::tick(const float dt)
{
    BroadPhase();
    for (std::shared_ptr<OObject> pObj : OObjectList) { //for each object
        //pObj->draw();
        if (pObj)
            pObj->tick(dt);
    } //for
}

//void OObjectManager::BroadPhase() {
//printf("COLLISON\n")


void OObjectManager::BroadPhase() {
    for (auto i = OObjectList.begin(); i != OObjectList.end(); i++) { //for each object
        // Skip static and non-collidable.
        if ((*i)->GetObjectCollisionType() == ECollisionType::None || (*i)->GetObjectCollisionType() == ECollisionType::Static)
            continue;
            for (auto j = next(i); j != OObjectList.end(); j++) { //for each later object
                if ((*i)->GetObjectCollisionType() == ECollisionType::None)
                    continue;
                NarrowPhase(*i, *j); //do narrow phase collision detection and response
            }
    }
    for (std::shared_ptr<OObject> pObj : OObjectList) //for each object
        if (pObj->GetObjectCollisionType() == ECollisionType::Dynamic) { //for each Dynamic object, that is
            for (int i = 0; i < 2; i++) { //can collide with 2 edges simultaneously
                Vector2 norm; //collision normal
                float d = 0; //overlap distance
                std::shared_ptr<OObject> CollisionObject = nullptr;
                BoundingSphere s(Vector3(pObj->GetWorldLocation()), pObj->GetRadius());
                // Check for nearby objects.
                // The radius sphere is going to let us check for nearby objects.
                // Let's focus on nearby dynamic objects first.
                // For all objects,
                // if within boundingsphere.
                // if dynamic
                // narrow collision.
                // else, static collision check maybe

                if (StaticCollisionCheck(s, norm, d, CollisionObject)) { //collide with wall
                    ICollision& pObjCol = *pObj;
                    pObjCol.Collision(norm, d, CollisionObject); //respond 
                }
            } //for
        } //for
} //BroadPhase

const bool OObjectManager::StaticCollisionCheck(
    BoundingSphere s, Vector2& norm, float& d, std::shared_ptr<OObject> c) const
{
    bool hit = false; //return result, true if there is a collision with a wall
    return false;
    for (std::shared_ptr<OObject> pObj : OObjectList){ //for each object
        if (pObj->GetObjectCollisionType() == ECollisionType::Dynamic) // skip Dynamic objects
            continue;
        const BoundingBox& aabb = *(pObj->GetBoundingBox());

        Vector3 corner[8]; //for corners of aabb
        aabb.GetCorners(corner);  //get corners of aabb
        s.Center.z = corner[0].z; //make sure they are at the same depth

        //the first 4 corners of aabb are the same as the last 4 but with different z

        hit = s.Intersects(aabb); //includes when they are touching

        if (hit) { //collision with either a point or an edge
            bool bPointCollide = false; //true if colliding with corner of bounding box
            c = pObj;
            for (UINT i = 0; i < 4 && !bPointCollide; i++) //check first 4 corners
                if (s.Contains(corner[i])) { //collision of bounding sphere with corner
                    bPointCollide = true;
                    Vector3 norm3 = s.Center - corner[i]; //vector from corner to sphere center
                    norm = (Vector2)norm3; //cast to 2D
                    d = s.Radius - norm.Length(); //overlap distance
                    norm.Normalize(); //norm needs to be a unit vector
                } //if

            if (!bPointCollide) { //edge collide
                const float fLeft = corner[0].x; //left of wall
                const float fRight = corner[1].x; //right of wall
                const float fBottom = corner[1].y; //bottom of wall
                const float fTop = corner[2].y; //top of wall

                const float epsilon = 0.01f; //small amount of separation

                if (s.Center.x <= fLeft) { //collide with left edge
                    norm = -Vector2::UnitX; //normal
                    d = s.Center.x - fLeft + s.Radius + epsilon; //overlap
                } //if

                else if (fRight <= s.Center.x) { //collide with right edge
                    norm = Vector2::UnitX; //normal
                    d = fRight - s.Center.x + s.Radius + epsilon; //overlap
                } //if

                else if (s.Center.y <= fBottom) { //collide with bottom edge
                    norm = -Vector2::UnitY; //normal
                    d = s.Center.y - fBottom + s.Radius + epsilon; //overlap
                } //if

                else if (fTop <= s.Center.y) { //collide with top edge
                    norm = Vector2::UnitY; //normal
                    d = fTop - s.Center.y + s.Radius + epsilon; //overlap
                } //if 
            } //if
        } //if
    } //for
}

OObjectManager::OObjectManager()
{
    this->m_pRenderer = OCommon::m_pRenderer;
}

/// Perform collision detection and response for a pair of objects. Makes
/// use of the helper function Identify() because this function may be called
/// with the objects in an arbitrary order.
/// \param p0 Pointer to the first object.
/// \param p1 Pointer to the second object.

void OObjectManager::NarrowPhase(std::shared_ptr<OObject> p0, std::shared_ptr<OObject> p1) {
    Vector2 vSep = p0->GetWorldLocation() - p1->GetWorldLocation(); //vector from *p1 to *p0
    const float d = p0->GetRadius() + p1->GetRadius() - vSep.Length(); //overlap

    if (d > 0.0f) { //bounding circles overlap
        vSep.Normalize(); //vSep is now the collision normal
        ICollision& pObjCol = *p0;
        ICollision& pObjCol1 = *p1;
        //printf("COLLISON\n");
        pObjCol.Collision(vSep, d, p1);
        //pObjCol.CollisionResponse(vSep, d, p1); //this changes separation of objects
        pObjCol1.Collision(-vSep, d, p0); //same separation and opposite normal
    } //if
} //NarrowPhase
