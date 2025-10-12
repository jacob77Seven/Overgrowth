#pragma once
class OObjectManager;
class OObject;
class IObjectUtilities {
protected:
    virtual void BeginPlay() = 0;
    virtual void OnDestroy() = 0;
    virtual void tick(const float dt) = 0;
    virtual void draw() = 0;
    friend class OObjectManager;
};
