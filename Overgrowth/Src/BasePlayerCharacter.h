#pragma once

#include "..\GameDefines.h"
#include "BaseCharacter.h"
#include "Component.h"

class OBasePlayerCharacter : public LComponent, public OBaseCharacter
{
protected:
    virtual void CollisionResponse(const Vector2&, float,
        std::weak_ptr<OObject> pObj); ///< Collision response.
    void KeyboardHandler();

    //const Vector2 GetViewVector() const; ///< Compute view vector.
    eSprite Sprite;
    virtual void OnDestroy() override;
    virtual void BeginPlay() override;
    float frame;
    float fps;
    float timeTrack;
public:
    OBasePlayerCharacter(const Vector3& p);
    float speed;
    //OObject();
    //virtual OObject(t, const Vector2&); ///< Constructor.
    //virtual ~TestCharacter(); ///< Destructor.
    virtual void tick(const float dt) override;
}; //OObject