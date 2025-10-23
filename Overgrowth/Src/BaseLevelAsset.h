/// \file Object.h
/// \brief Interface for the game object class OObject.

#pragma once

#include "..\GameDefines.h"
#include "SpriteRenderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"
#include "Object.h"
#include "EventTimer.h"
#include "ComponentIncludes.h"

/// \brief The game object. 
///
/// The abstract representation of an object. This class must contain public member
/// functions `move()` and `draw()` to move and draw the object, respectively.

class OBaseLevelAsset :
    public OObject
{
protected:
    float m_fRadius = 0; ///< Bounding circle radius.
	bool collidable = false; ///< Is collidable.
	Vector2 Scale = Vector2(1.0f, 1.0f); ///< Scale.
    eSprite Sprite;
    virtual void OnDestroy() override;
    virtual void BeginPlay() override;

public:
    OBaseLevelAsset(const Vector3& p);
    virtual ~OBaseLevelAsset(); ///< Destructor.
}; //OObject