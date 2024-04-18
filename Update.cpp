#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
    if (m_NewLevelRequired)
    {
        // Load level
        loadLevel();
    }

    if (m_Playing)
    {
        m_Thomas.update(dtAsSeconds);
        m_Bob.update(dtAsSeconds);

        // Detect collisions and see if characters have reached the goal
        // Second part of if condition is executed only when Thomas touches the home tile
        if (detectCollisions(m_Thomas) && detectCollisions(m_Bob))
        {
            m_NewLevelRequired = true;
            // Play reach goal sound
        }
        else
        {
            detectCollisions(m_Bob);
        }

        // Let Bob and Thomas jump on each others' heads
        if (m_Bob.getFeet().intersects(m_Thomas.getHead()))
        {
            m_Bob.stopFalling(m_Thomas.getHead().top);
        }
        else if (m_Thomas.getFeet().intersects(m_Bob.getHead()))
        {
            m_Thomas.stopFalling(m_Bob.getHead().top);
        }

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