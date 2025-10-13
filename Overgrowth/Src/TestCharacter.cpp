#include "TestCharacter.h"

#include "ObjectManager.h"
#include "TestObject.h"

void TestCharacter::BeginPlay()
{
    OBaseCharacter::BeginPlay(); // Call to parent class.
    printf("Character Begin Play!");
    // This code is a test of the garbage collection system.
    //std::weak_ptr<TestObject> object = OCommon::m_pObjectManager->create<TestObject>(m_vPos + Vector3(100, 100, 0));
    //if (auto obj = object.lock())
    //    obj->Destroy();
}

TestCharacter::TestCharacter(const Vector3& p) 
    : OBaseCharacter(p)
{
    speed = 200.f * OCommon::m_fTile;
    m_nSpriteIndex = (UINT)eSprite::Pig;
    EObjectCollisionType = ECollisionType::Dynamic;
    m_nCurrentFrame = 0;
    printf("TestCharacter has become -  %f, %f, %f\n", m_vPos.x, m_vPos.y, m_vPos.z);
}

void TestCharacter::OnDestroy() {
    OBaseCharacter::OnDestroy();
}

void TestCharacter::tick(const float dt) {

    m_vPos.y -= dt * speed;
    //printf("m_vPos.y = %f & dt = %f\n", m_vPos.y, dt);
    OBaseCharacter::tick(dt);
}

/// Ask the renderer to draw the sprite described in the sprite descriptor.
/// Note that `OObject` is derived from `LBaseObject` which is inherited from
/// `LSpriteDesc2D`. Therefore `LSpriteRenderer::Draw(const LSpriteDesc2D*)`
/// will accept `this` as a parameter, automatically down-casting it from
/// `OObject*` to `LSpriteDesc2D*`, effectively drawing the object from its
/// sprite descriptor.

void TestCharacter::CollisionResponse(const Vector2& norm, float d, OObject* pObj) {

}