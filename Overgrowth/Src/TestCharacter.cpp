#include "TestCharacter.h"

TestCharacter::TestCharacter(eSprite t, const Vector2& p)
    : OBaseCharacter(t, p)
{
    printf("Test Character Created!!\n");
}


TestCharacter::TestCharacter(const Vector2& p)
    : OBaseCharacter(p)
{
    EObjectCollisionType = ECollisionType::Dynamic;
    printf("Test Character Created (Location only given)!!\n");
}

TestCharacter::~TestCharacter() {

}

void TestCharacter::tick(const float dt) {
    m_vPos.y -= dt * speed;
    OBaseCharacter::tick(dt);
}

void TestCharacter::move() {
    if (!m_bDead && !m_bStatic)
        m_vPos += m_vVelocity * m_pTimer->GetFrameTime();
} //move

/// Ask the renderer to draw the sprite described in the sprite descriptor.
/// Note that `OObject` is derived from `LBaseObject` which is inherited from
/// `LSpriteDesc2D`. Therefore `LSpriteRenderer::Draw(const LSpriteDesc2D*)`
/// will accept `this` as a parameter, automatically down-casting it from
/// `OObject*` to `LSpriteDesc2D*`, effectively drawing the object from its
/// sprite descriptor.

void TestCharacter::draw() {
    m_pRenderer->Draw(this);
} //draw

void TestCharacter::CollisionResponse(const Vector2& norm, float d, OObject* pObj) {

}