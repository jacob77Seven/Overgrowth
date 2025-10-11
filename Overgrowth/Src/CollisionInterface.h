#pragma once
class OObjectManager;
class OObject;
class ICollision {
protected:
    virtual void Collision(const Vector2& norm, float d, std::shared_ptr<OObject> pObj) = 0;
    friend class OObjectManager;
};
