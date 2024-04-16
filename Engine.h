#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Bob.h"
#include "Thomas.h"

using namespace sf;

class Engine
{
    private:
        TextureHolder th;

        // Thomas and Bob, playable characters
        Thomas m_Thomas;
        Bob m_Bob;

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

        void input();
        void update(float dtAsSeconds);
        void draw();

    public:
        Engine();
        void run();
};
