#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
    if (m_NewLevelRequired)
    {
        // To be moved to a new loadLevel function later
        m_Thomas.spawn(Vector2f(0, 0), GRAVITY);
        m_Bob.spawn(Vector2f(100, 0), GRAVITY);

        // Make sure spawn is called only once
        m_TimeRemaining = 10;
        m_NewLevelRequired = false;
    }

    if (m_Playing)
    {
        m_Thomas.update(dtAsSeconds);
        m_Bob.update(dtAsSeconds);

        // Count down time remaining
        m_TimeRemaining -= dtAsSeconds;

        // Have Thomas and Bob run out of time?
        if (m_TimeRemaining <= 0)
        {
            m_NewLevelRequired = true;
        }
    } // end if playing

    // Set appropriate view for character
    if (m_SplitScreen)
    {
        m_LeftView.setCenter(m_Thomas.getCenter());
        m_RightView.setCenter(m_Bob.getCenter());
    }
    else
    {
        // Center full screen around appropriate character
        if (m_Character1)
        {
            m_MainView.setCenter(m_Thomas.getCenter());
        }
        else
        {
            m_MainView.setCenter(m_Bob.getCenter());
        }
    }
}