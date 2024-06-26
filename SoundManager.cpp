#include "SoundManager.h"
#include <SFML/Audio.hpp>

using namespace sf;

SoundManager::SoundManager()
{
    // Load sounds into buffers
    m_FireBuffer.loadFromFile("sound/fire1.wav");
    m_FallInFireBuffer.loadFromFile("sound/fallinfire.wav");
    m_FallInWaterBuffer.loadFromFile("sound/fallinwater.wav");
    m_JumpBuffer.loadFromFile("sound/jump.wav");
    m_ReachGoalBuffer.loadFromFile("sound/reachgoal.wav");

    // Associate sounds with buffers
    m_Fire1Sound.setBuffer(m_FireBuffer);
    m_Fire2Sound.setBuffer(m_FireBuffer);
    m_Fire3Sound.setBuffer(m_FireBuffer);
    m_FallInFireSound.setBuffer(m_FallInFireBuffer);
    m_FallInWaterSound.setBuffer(m_FallInWaterBuffer);
    m_JumpSound.setBuffer(m_JumpBuffer);
    m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);

    // Sound at full volume when player is 50 pixels away
    float minDistance = 150;
    // Sound reduces steadily as player moves further away
    float attenuation = 15;

    // Set attentuation levels
    m_Fire1Sound.setAttenuation(attenuation);
    m_Fire2Sound.setAttenuation(attenuation);
    m_Fire3Sound.setAttenuation(attenuation);

    // Set minimum distance levels
    m_Fire1Sound.setMinDistance(minDistance);
    m_Fire2Sound.setMinDistance(minDistance);
    m_Fire3Sound.setMinDistance(minDistance);

    // Loop the fire sounds when they are played
    m_Fire1Sound.setLoop(true);
    m_Fire2Sound.setLoop(true);
    m_Fire3Sound.setLoop(true);
}

void SoundManager::playFire(Vector2f emitterLocation, Vector2f listenerLocation)
{
    // Where is the listener?
    Listener::setPosition(
        listenerLocation.x,
        listenerLocation.y,
        0.0f
    );

    switch(m_NextSound)
    {
        case 0:
            // Locate or move the source of the sound
            m_Fire1Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);
            if (m_Fire1Sound.getStatus() == Sound::Status::Stopped)
            {
                m_Fire1Sound.play();
            }
            break;

        case 1:
            // Same as above
            m_Fire2Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);
            if (m_Fire2Sound.getStatus() == Sound::Status::Stopped)
            {
                m_Fire2Sound.play();
            }
            break;

        case 2:
        m_Fire3Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);
            if (m_Fire3Sound.getStatus() == Sound::Status::Stopped)
            {
                m_Fire3Sound.play();
            }
            break;
    }

    // next fire sound
    m_NextSound = (m_NextSound + 1) % 3;
}

void SoundManager::playFallInFire()
{
    m_FallInFireSound.setRelativeToListener(true);
    m_FallInFireSound.play();
}

void SoundManager::playFallInWater()
{
    m_FallInFireSound.setRelativeToListener(true);
    m_FallInFireSound.play();
}

void SoundManager::playJump()
{
    m_JumpSound.setRelativeToListener(true);
    m_JumpSound.play();
}

void SoundManager::playReachGoal()
{
    m_ReachGoalSound.setRelativeToListener(true);
    m_ReachGoalSound.play();
}