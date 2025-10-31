#include "ObjectManager.h"
#include "TestObject.h"

#include "BasePlayerCharacter.h"

OBasePlayerCharacter::OBasePlayerCharacter(const Vector3& p)
    : OBaseCharacter(p)
{
    speed = 40.f;
    m_nSpriteIndex = (UINT)eSprite::walkright;
    EObjectCollisionType = ECollisionType::Dynamic;
    m_nCurrentFrame = 0;
    //printf("OBasePlayerCharacter has become -  %f, %f, %f\n", m_vPos.x, m_vPos.y, m_vPos.z);
    fps = 6.f;
    frame = 0.f;
}

void OBasePlayerCharacter::OnDestroy() {
    OBaseCharacter::OnDestroy();
}

void OBasePlayerCharacter::tick(const float dt) {
    KeyboardHandler();
    //timeTrack += dt;
    //printf("time %.8f\n", timeTrack);
    //m_vPos.x += dt * speed;
    //printf("m_vPos.y = %f & dt = %f\n", m_vPos.y, dt);
    OBaseCharacter::tick(dt);
    frame += dt * fps;
    if (frame >= 8.f)
        frame = frame - 8;

    m_nCurrentFrame = (UINT)floor(frame);
}

/// Ask the renderer to draw the sprite described in the sprite descriptor.
/// Note that `OObject` is derived from `LBaseObject` which is inherited from
/// `LSpriteDesc2D`. Therefore `LSpriteRenderer::Draw(const LSpriteDesc2D*)`
/// will accept `this` as a parameter, automatically down-casting it from
/// `OObject*` to `LSpriteDesc2D*`, effectively drawing the object from its
/// sprite descriptor.

void OBasePlayerCharacter::CollisionResponse(const Vector2& norm, float d, OObject* pObj) {

}

void OBasePlayerCharacter::BeginPlay()
{
    timeTrack = 0;
    OBaseCharacter::BeginPlay(); // Call to parent class.
    //printf("Character Begin Play!");
    // This code is a test of the garbage collection system.
    //std::weak_ptr<TestObject> object = OCommon::m_pObjectManager->create<TestObject>(m_vPos + Vector3(100, 100, 0));
    //if (auto obj = object.lock())
    //    obj->Destroy();
}



void OBasePlayerCharacter::KeyboardHandler() {
    m_pKeyboard->GetState(); //get current keyboard state 

    if (m_pKeyboard->Down(VK_SPACE)){ //play sound
            m_pAudio->play(eSound::clang);
            printf("Noise!!!\n");
    }

    if (m_pKeyboard->TriggerDown('O'))
        m_pAudio->play(eSound::oink);

    if (m_pKeyboard->TriggerDown('P'))
        m_pAudio->play(eSound::piano);

    if (m_pKeyboard->Down(VK_LEFT))  m_vPos.x -= 5.0f;

    if (m_pKeyboard->Down(VK_RIGHT)) m_vPos.x += 5.0f;

    if (m_pKeyboard->Down(VK_UP))    m_vPos.y += 5.0f;

    if (m_pKeyboard->Down(VK_DOWN))  m_vPos.y -= 5.0f;

} //KeyboardHandler