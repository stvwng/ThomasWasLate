#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager
{
    private:
        SoundBuffer m_FireBuffer;
        SoundBuffer m_FallInFireBuffer;
        SoundBuffer m_FallInWaterBuffer;
        SoundBuffer m_JumpBuffer;
        SoundBuffer m_ReachGoalBuffer;

        Sound m_Fire1Sound;
        Sound m_Fire2Sound;
        Sound m_Fire3Sound;
        Sound m_FallInFireSound;
        Sound m_FallInWaterSound;
        Sound m_JumpSound;
        Sound m_ReachGoalSound;

        // Which sound to use next: Fire 1, 2, or 3
        int m_NextSound = 0;

    public:

        SoundManager();

        void playFire(Vector2f emitterLocation, Vector2f listenerLocation);

        void playFallInFire();
        void playFallInWater();
        void playJump();
        void playReachGoal();

};