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
#include <memory>
#include <type_traits>

/// \brief The object manager handles calling rendering and running 
/// collision checks on all the game objects.

class OObjectManager :
    public LBaseObjectManager<OObject>,
    public OCommon
{
private:
    void BroadPhase(); ///< Broad phase collision detection and response.
    void NarrowPhase(std::shared_ptr<OObject>, std::shared_ptr<OObject>); ///< Narrow phase collision detection and response.
    static std::vector<std::shared_ptr<OObject>> OObjectList;
    // OObject* c is the collided object from the static list.
    const bool StaticCollisionCheck(BoundingSphere s, Vector2& norm, float& d, std::shared_ptr<OObject> c) const;
    
public:
    OObjectManager();
    template <typename T>
    // DEPRACATED
    //OObject* create(eSprite esp, const Vector2&); ///< Create new object.
    // The Factory is now much simpler.
    static std::shared_ptr<T> create(const Vector2& pos) {
        static_assert(std::is_base_of<OObject, T>::value, "T must be a descendant of OObject");
        std::shared_ptr<T> pObj = std::make_shared<T>(pos);
        OObjectList.push_back(pObj);
        return pObj;
    }
    virtual void draw(); ///< Draw all objects.
    virtual void tick(const float dt);

    //void FireGun(OObject*, eSprite); ///< Fire object's gun.
    //const size_t GetNumTurrets() const; ///< Get number of turrets in object list.
}; //OObjectManager

#endif //__L4RC_GAME_OBJECTMANAGER_H__
