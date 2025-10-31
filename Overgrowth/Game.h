/// \file Game.h
/// \brief Interface for the game class CGame.

#ifndef __L4RC_GAME_GAME_H__
#define __L4RC_GAME_GAME_H__

#include "Component.h"
#include "Settings.h"
#include "SpriteDesc.h"
#include "Src/Renderer.h"
#include "Src/LevelImporter.h"
#include "Src/Common.h"
#include "Src/ObjectManager.h"

/// \brief The game class.
///
/// The game class is the object-oriented implementation of the game. This class
/// must contain the following public member functions. `Initialize()` does
/// initialization and will be run exactly once at the start of the game.
/// `ProcessFrame()` will be called once per frame to create and render the
/// next animation frame. `Release()` will be called at game exit but before
/// any destructors are run.

class OAssetLoader;
class OBasePlayerCharacter;
class CGame: 
  public LComponent, 
  public LSettings,
  public OCommon { 

  private:
    bool m_bDrawFrameRate = false; ///< Draw the frame rate.
    LSpriteDesc2D* m_pSpriteDesc = nullptr; ///< Sprite descriptor.
    LSpriteDesc3D* m_pSquareDesc = nullptr;
    std::weak_ptr<OBasePlayerCharacter> MainCharacter;
    ORenderer* m_pRenderer = nullptr; ///< Pointer to renderer.
    OObjectManager* m_pObjectManager = nullptr; ///< Pointer to renderer.
    LevelImporter* LvlImporter = nullptr;
    OAssetLoader* m_pAssetLoader = nullptr;
    Vector2 m_vCameraPos;
    LBaseCamera* m_pCamera = nullptr;

    void LoadLevels(); ///< Load levels.
    void BeginGame(); ///< Begin playing the game.
    //void CreateObjects(); ///< Create game objects.
    void KeyboardHandler(); ///< The keyboard handler.
    void RenderFrame(); ///< Render an animation frame.
    void DrawFrameRateText(); ///< Draw frame rate text to screen.

  public:
    std::vector<LSpriteDesc3D*> m_vLevelSprites; //container for storing tiles
    ~CGame(); ///< Destructor.

    void Initialize(); ///< Initialize the game.
    void ProcessFrame(); ///< Process an animation frame.
    void Release(); ///< Release the renderer.
}; //CGame

#endif //__L4RC_GAME_GAME_H__
