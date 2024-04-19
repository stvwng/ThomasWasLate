#include "Engine.h"

void Engine::draw()
{
    // Clear previous frame
    m_Window.clear(Color::White);

    // Update shader parameters
    m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());

    if (!m_SplitScreen)
    {
        // Switch to background view
        m_Window.setView(m_BGMainView);

        // Draw background with shader effect
        m_Window.draw(m_BackgroundSprite, &m_RippleShader);

        // Switch to main view
        m_Window.setView(m_MainView);

        // Draw level
        m_Window.draw(m_VALevel, &m_TextureTiles);

        m_Window.draw(m_Thomas.getSprite());
        m_Window.draw(m_Bob.getSprite());

        // Draw particle system
        if (m_PS.running())
        {
            m_Window.draw(m_PS);
        }
    }
    else
    {
        // Split screen is active

        // Draw Thomas' side of the screen
        // Switch to background view
        m_Window.setView(m_BGLeftView);
        // Draw background with shader effect
        m_Window.draw(m_BackgroundSprite, &m_RippleShader);
        // Switch to LeftView
        m_Window.setView(m_LeftView);

        // Draw level
        m_Window.draw(m_VALevel, &m_TextureTiles);

        m_Window.draw(m_Bob.getSprite());
        m_Window.draw(m_Thomas.getSprite());

        // Draw particle system
        if (m_PS.running())
        {
            m_Window.draw(m_PS);
        }

        // Draw Bob's side of the screen
        // Switch to background view
        m_Window.setView(m_BGRightView);
        // Draw background with shader effect
        m_Window.draw(m_BackgroundSprite, &m_RippleShader);
        // Switch to RightView
        m_Window.setView(m_BGRightView);

        // Draw level
        m_Window.draw(m_VALevel, &m_TextureTiles);

        m_Window.draw(m_Bob.getSprite());
        m_Window.draw(m_Thomas.getSprite());

        // Draw particle system
        if (m_PS.running())
        {
            m_Window.draw(m_PS);
        }
    }

    // Draw HUD
    // Switch to HudView
    m_Window.setView(m_HudView);
    m_Window.draw(m_Hud.getLevel());
    m_Window.draw(m_Hud.getTime());
    if (!m_Playing)
    {
        m_Window.draw(m_Hud.getMessage());
    }

    // Show everything we've drawn
    m_Window.display();
}
