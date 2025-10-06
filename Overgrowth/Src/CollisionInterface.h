#pragma once
class OObjectManager;
class OObject;
class ICollision {
protected:
    virtual void CollisionResponse(const Vector2& norm, float d, OObject* pObj) = 0;
    friend class OObjectManager;
};
