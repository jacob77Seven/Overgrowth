#pragma once
/// \file Common.h
/// \brief Interface for the class OCommon.

#include "Defines.h"

#include "SpriteRenderer.h"
//forward declarations to make the compiler less stroppy

class OObjectManager;
class ORenderer;
//class LSpriteRenderer;
class LParticleEngine2D;
class CTileManager;
class CPlayer;
class CUIManager;
class IInput;

#include "../GameDefines.h"

/// \brief The common variables class.
///
/// OCommon is a singleton class that encapsulates things that are common to
/// different game components, including game state variables. Making it a
/// singleton class means that we can avoid passing its member variables
/// around as parameters, which makes the code minisculely faster, and more
/// importantly, makes the code more readable by reducing function clutter.

class OCommon : OAssetDefines {
protected:
    static ORenderer* m_pRenderer; ///< Pointer to renderer.
    static OObjectManager* m_pObjectManager; ///< Pointer to object manager.
    static LParticleEngine2D* m_pParticleEngine; ///< Pointer to particle engine.
    static CTileManager* m_pTileManager; ///< Pointer to tile manager. 
	static CUIManager* m_pUIManager;
	static std::vector<IInput*> m_pInputManager;

    static bool m_bDrawAABBs; ///< Draw AABB flag.
    static bool m_bGodMode; ///< God mode flag.
	static float m_fCameraPosZ;

    static Vector2 m_vWorldSize; ///< World height and width.
    static CPlayer* m_pPlayer; ///< Pointer to player character.
    static float m_fTile;

    UINT GetSpriteHandleIndex(const std::string handle);
    UINT GetSoundHandleIndex(const std::string handle);
}; //OCommon