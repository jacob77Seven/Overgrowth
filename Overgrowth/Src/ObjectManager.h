/// \file ObjectManager.h
/// \brief Interface for the object manager OObjectManager.

#ifndef __L4RC_GAME_OBJECTMANAGER_H__
#define __L4RC_GAME_OBJECTMANAGER_H__

#include <iostream>
#include <type_traits>
#include "BaseObjectManager.h"
#include "Object.h"
#include "Common.h"
#include "CollisionInterface.h"

/// \brief The object manager handles calling rendering and running 
/// collision checks on all the game objects.

class OObjectManager :
    public LBaseObjectManager<OObject>,
    public OCommon
{
private:
    void BroadPhase(); ///< Broad phase collision detection and response.
    //void NarrowPhase(OObject*, OObject*); ///< Narrow phase collision detection and response.
    static std::vector<OObject*> OObjectList;
    // OObject* c is the collided object from the static list.
    const bool StaticCollisionCheck(BoundingSphere s, Vector2& norm, float& d, OObject* c) const;

public:
    template <typename T>
    // DEPRACATED
    //OObject* create(eSprite esp, const Vector2&); ///< Create new object.
    // The Factory is now much simpler.
    static T* create(const Vector2& pos) {
        static_assert(std::is_base_of<OObject, T>::value, "T must be a descendant of OObject");
        T* pObj = new T(pos);
        OObjectList.push_back(pObj);
        return pObj;
    }

    //virtual void draw(); ///< Draw all objects.

    //void FireGun(OObject*, eSprite); ///< Fire object's gun.
    //const size_t GetNumTurrets() const; ///< Get number of turrets in object list.
}; //OObjectManager

#endif //__L4RC_GAME_OBJECTMANAGER_H__
