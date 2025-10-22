/// \file Game.cpp
/// \brief Code for the game class CGame.

#include "Game.h"

#include "GameDefines.h"
#include "ComponentIncludes.h"
#include "Src\TestCharacter.h"
#include "shellapi.h"
#include "Src\Common.h"

/// Delete the sprite descriptor. The renderer needs to be deleted before this
/// destructor runs so it will be done elsewhere.

CGame::~CGame(){
    delete m_pSpriteDesc;
} //destructor

/// Create the renderer and the sprite descriptor load images and sounds, and
/// begin the game.

void CGame::Initialize(){
    // Initialize the camera
    m_pCamera = new LBaseCamera();
    m_pCamera->SetPerspective(45.0f * XM_PI / 180.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);
    m_pCamera->MoveTo(Vector3(0, 0, 50));
    m_pCamera->MoveTo(m_pCamera->GetPos());

    m_pRenderer = new ORenderer(eSpriteMode::Unbatched3D);
    OCommon::m_pRenderer = m_pRenderer;
    m_pRenderer->Initialize(5, 16); 
    m_pObjectManager = new OObjectManager();
    OCommon::m_pObjectManager = m_pObjectManager;

    LoadImages(); //load images from xml file list
    LoadSounds(); //load the sounds for this game
    LoadLevels();
    BeginGame();
} //Initialize

/// Load the specific images needed for this game. This is where `eSprite`
/// values from `GameDefines.h` get tied to the names of sprite tags in
/// `gamesettings.xml`. Those sprite tags contain the name of the corresponding
/// image file. If the image tag or the image file are missing, then the game
/// should abort from deeper in the Engine code leaving you with an error
/// message in a dialog box.

void CGame::LoadImages(){  
    m_pRenderer->BeginResourceUpload();

    m_pRenderer->Load(eSprite::Background, "background"); 
    m_pRenderer->Load(eSprite::TextWheel,  "textwheel"); 
    m_pRenderer->Load(eSprite::Pig,  "pig"); 
    m_pRenderer->Load(eSprite::Pink_sheet,  "pink_sheet");
    //m_pRenderer->LoadSpriteSheet((UINT)eSprite::Pink_sheet, "pink_sheet", 8, 8, 16);

    m_pRenderer->LoadSpriteSheet((UINT)eSprite::Pink_sheet, "pink_sheet", 8, 8, 16);

    m_pRenderer->Load(eSprite::PinkSquare, "pinksquare");

    m_pRenderer->EndResourceUpload();
} //LoadImages

// Load Levels
void CGame::LoadLevels() {
    LvlImporter = new LevelImporter();
    //LvlImporter->Initialize(eLevels::Size);
    LvlImporter->Load((int)eLevels::RealLevel, "reallevel");

} //LoadLevels

/// Initialize the audio player and load game sounds.

void CGame::LoadSounds(){
    m_pAudio->Initialize(eSound::Size);
    m_pAudio->Load(eSound::Grunt, "grunt");
    m_pAudio->Load(eSound::Clang, "clang");
    m_pAudio->Load(eSound::Oink, "oink");
    m_pAudio->Load(eSound::Piano, "piano");

} //LoadSounds

/// Release all of the DirectX12 objects by deleting the renderer.

void CGame::Release(){
  delete m_pRenderer;
  m_pRenderer = nullptr; //for safety
} //Release

/// Call this function to start a new game. This should be re-entrant so that
/// you can restart a new game without having to shut down and restart the
/// program.

void CGame::BeginGame(){  
    delete m_pSpriteDesc;
    delete m_pSquareDesc;
    //m_pSpriteDesc = new LSpriteDesc3D((UINT)eSprite::TextWheel, m_vWinCenter);
    m_pSquareDesc = new LSpriteDesc3D();
    //m_pSquareDesc->m_nSpriteIndex = (UINT)eSprite::PinkSquare;
    m_pSquareDesc->m_nSpriteIndex = (UINT)7;
    //m_pSquareDesc->m_nCurrentFrame = 1;
    m_pSquareDesc->m_vPos = Vector3(m_vWinCenter.x, m_vWinCenter.y, 0.0f);
    m_pSquareDesc->m_fXScale = 4.0f;
    m_pSquareDesc->m_fYScale = 4.0f;
    m_pSquareDesc->m_fRoll = 0.0f;
    m_pSquareDesc->m_fAlpha = 1.0f;
    m_pSquareDesc->m_f4Tint = Vector4(1, 1, 1, 1);

    if ((LvlImporter == nullptr)) {
        printf("No levels loaded!\n");
	    return;
    }
    m_pObjectManager;
    auto character = m_pObjectManager->create<TestCharacter>(Vector3(m_vWinCenter.x + 0, m_vWinCenter.y + 400, 0));
    auto character2 = m_pObjectManager->create<TestCharacter>(Vector3(m_vWinCenter.x, m_vWinCenter.y - 400, 0));
    if (auto char2 = character2.lock()) {
        char2->speed = char2->speed * 0;
        char2->SetObjectCollisionType(ECollisionType::Static);
    }

    LevelData& data = LvlImporter->GetLevelData(); //get first level for now

    // Debug print tiles
    for (auto& t : data.tiles) {
        printf("Tile %d at (%d,%d), src=(%d,%d)\n",
            t.tileID, t.posX, t.posY, t.srcX, t.srcY);
    }

    for (auto* s : m_vLevelSprites) delete s; //clean up old level sprites
    m_vLevelSprites.clear();

    // Build sprite descriptors for each tile
    for (auto& t : data.tiles) {
        auto* desc3D = new LSpriteDesc3D();
        desc3D->m_nSpriteIndex = (UINT)eSprite::PinkSquare;
        desc3D->m_vPos = Vector3((float)t.posX, (float)t.posY, t.posZ);
        desc3D->m_fXScale = 1.0f;
        desc3D->m_fYScale = 1.0f;
        desc3D->m_fRoll = 0.0f;
        desc3D->m_fAlpha = 1.0f;
        desc3D->m_f4Tint = Vector4(1, 1, 1, 1);
        m_vLevelSprites.push_back(desc3D);
    }

} //BeginGame

/// Poll the keyboard state and respond to the key presses that happened since
/// the last frame.

void CGame::KeyboardHandler(){
    m_pKeyboard->GetState(); //get current keyboard state 
  
    if(m_pKeyboard->TriggerDown(VK_F1)) //help
        ShellExecute(0, 0, "https://larc.unt.edu/code/physics/blank/", 0, 0, SW_SHOW);
  
    if(m_pKeyboard->TriggerDown(VK_F2)) //toggle frame rate 
        m_bDrawFrameRate = !m_bDrawFrameRate;
  
    if(m_pKeyboard->TriggerDown(VK_SPACE)) //play sound
        m_pAudio->play(eSound::Clang);

    if(m_pKeyboard->TriggerUp(VK_SPACE)) //play sound
        m_pAudio->play(eSound::Grunt);
  
    if (m_pKeyboard->TriggerDown('O'))
        m_pAudio->play(eSound::Oink);

    if (m_pKeyboard->TriggerDown('P'))
        m_pAudio->play(eSound::Piano);

    if (m_pKeyboard->Down(VK_LEFT))  m_pSquareDesc->m_vPos.x -= 5.0f;
        
    if (m_pKeyboard->Down(VK_RIGHT)) m_pSquareDesc->m_vPos.x += 5.0f;
        
    if (m_pKeyboard->Down(VK_UP))    m_pSquareDesc->m_vPos.y += 5.0f;
        
    if (m_pKeyboard->Down(VK_DOWN))  m_pSquareDesc->m_vPos.y -= 5.0f;
        
    if(m_pKeyboard->TriggerDown(VK_BACK)) //restart game
        BeginGame(); //restart game
} //KeyboardHandler

/// Draw the current frame rate to a hard-coded position in the window.
/// The frame rate will be drawn in a hard-coded position using the font
/// specified in gamesettings.xml.

void CGame::DrawFrameRateText(){
      const std::string s = std::to_string(m_pTimer->GetFPS()) + " fps"; //frame rate
      const Vector2 pos(m_nWinWidth - 128.0f, 30.0f); //hard-coded position
      m_pRenderer->DrawScreenText(s.c_str(), pos); //draw to screen
} //DrawFrameRateText

/// Draw the game objects. The renderer is notified of the start and end of the
/// frame so that it can let Direct3D do its pipelining jiggery-pokery.

void CGame::RenderFrame(){
    m_pRenderer->BeginFrame(); //required before rendering

    for (auto* desc3D : m_vLevelSprites) {
        m_pRenderer->Draw(desc3D);
    }

    if (m_pSquareDesc) {
        
        m_pRenderer->Draw(m_pSquareDesc);
    }
    OCommon::m_pObjectManager->draw();

    if(m_bDrawFrameRate)DrawFrameRateText(); //draw frame rate, if required

    m_pRenderer->EndFrame(); //required after rendering
} //RenderFrame

/// This function will be called regularly to process and render a frame
/// of animation, which involves the following. Handle keyboard input.
/// Notify the  audio player at the start of each frame so that it can prevent
/// multiple copies of a sound from starting on the same frame.  
/// Move the game objects. Render a frame of animation.

void CGame::ProcessFrame(){
    KeyboardHandler(); //handle keyboard input
    m_pAudio->BeginFrame(); //notify audio player that frame has begun

    m_pTimer->Tick([&](){ //all time-dependent function calls should go here
    const float t = m_pTimer->GetFrameTime(); //frame interval in seconds
    //m_pSpriteDesc->m_fRoll += 0.125f*XM_2PI*t; //rotate at 1/8 RPS

    if (m_pSquareDesc) {
        // Follow player smoothly
        const float followSpeed = 5.0f;
        Vector3 playerPos = Vector3(m_pSquareDesc->m_vPos.x, m_pSquareDesc->m_vPos.y, m_pSquareDesc->m_vPos.z);
        m_vCameraPos += (playerPos - m_vCameraPos) * followSpeed * t;

        if (m_pCamera)
            m_pCamera->MoveTo(Vector3(m_vCameraPos.x, m_vCameraPos.y, -1000.0f));
    }
    });
    m_pTimer->Tick([&](){ //all time-dependent function calls should go here
        const float t = m_pTimer->GetFrameTime(); //frame interval in seconds
        //m_pSpriteDesc->m_fRoll += 0.125f*XM_2PI*t; //rotate at 1/8 RPS
        if (OCommon::m_pObjectManager)
            OCommon::m_pObjectManager->tick(t);
    });

    RenderFrame(); //render a frame of animation
} //ProcessFrame