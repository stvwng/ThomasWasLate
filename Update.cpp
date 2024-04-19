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
            m_SM.playReachGoal();
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

    // Check if a fire sound needs to be played
    vector<Vector2f>::iterator it;
    for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
    {
        // Where is the emitter?
        float posX = it->x;
        float posY = it->y;

        // Is the emitter near the player?
        // Make a 500 pixel rectangle around the emitter
        FloatRect localRect(posX - 250, posY - 250, 500, 500);

        // Is player inside localRect?
        if (m_Thomas.getPosition().intersects(localRect))
        {
            // Play the sound and pass in the location
            m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
        }
    }

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

    // Time to update the HUD?
    // Increment number of frames since last HUD calculation
    m_FramesSinceLastHUDUpdate++;

    // Update the HUD every m_TargetFramesPerHUDUpdate frames
    if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
    {
        // Update game HUD text
        stringstream ssTime;
        stringstream ssLevel;

        // Update time text
        ssTime << (int)m_TimeRemaining;
        m_Hud.setTime(ssTime.str());

        // Update level text
        ssLevel << "Level: " << m_LM.getCurrentLevel();
        m_Hud.setLevel(ssLevel.str());

        m_FramesSinceLastHUDUpdate = 0;
    }

    // Update the particles
    if (m_PS.running())
    {
        m_PS.update(dtAsSeconds);
    }
}