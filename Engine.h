#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Bob.h"
#include "Thomas.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"

using namespace sf;

class Engine
{
    private:
        TextureHolder th;

        // Create a particle system
        ParticleSystem m_PS;

        // Thomas and Bob, playable characters
        Thomas m_Thomas;
        Bob m_Bob;

        // Class to manage levels
        LevelManager m_LM;

        // Create a SoundManager
        SoundManager m_SM;

        // HUD
        Hud m_Hud;
        int m_FramesSinceLastHUDUpdate = 0;
        int m_TargetFramesPerHUDUpdate = 500;

        const int TILE_SIZE = 50;
        const int VERTS_IN_QUAD = 4;
        const int GRAVITY = 300;

        RenderWindow m_Window;

        // main views
        View m_MainView;
        View m_LeftView;
        View m_RightView;

        // background views
        View m_BGMainView;
        View m_BGLeftView;
        View m_BGRightView;

        View m_HudView;

        Sprite m_BackgroundSprite;
        Texture m_BackgroundTexture;

        // Declare a shader for the background
        Shader m_RippleShader;

        // is game currently playing?
        bool m_Playing = false;

        // is character 1 or character 2 the current focus?
        bool m_Character1 = true;

        // Start in full screen (not split) mode
        bool m_SplitScreen = false;

        // time left in current level in seconds
        float m_TimeRemaining = 10;
        Time m_GameTimeTotal;

        bool m_NewLevelRequired = true;

        // Vertex array for the level tiles
        VertexArray m_VALevel;

        // 2d array with map for level (pointer to pointer)
        int** m_ArrayLevel = NULL;

        // Texture for the level tiles
        Texture m_TextureTiles;

        void input();
        void update(float dtAsSeconds);
        void draw();
        void loadLevel();
        bool detectCollisions(PlayableCharacter& character);

        // Vector of the best places to emit sounds from
        void populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel);

        // Vector of Vector2f for the fire emitter locations
        vector <Vector2f> m_FireEmitters;

    public:
        Engine();
        void run();
};
