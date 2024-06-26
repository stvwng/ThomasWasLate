#include "Engine.h"

bool Engine::detectCollisions(PlayableCharacter& character)
{
    bool reachedGoal = false;
    // Make a rect for character parts
    FloatRect detectionZone = character.getPosition();

    // Make a FloatRect to test each part
    FloatRect block;

    block.width = TILE_SIZE;
    block.height = TILE_SIZE;

    // Build a zone around the character to detect collisions
    int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
    int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
    int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
    int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

    // Don't test positions lower than 0 or higher than end of array
    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX >= m_LM.getLevelSize().x) endX = m_LM.getLevelSize().x;
    if (endY >= m_LM.getLevelSize().y) endY = m_LM.getLevelSize().y;

    // Has the character fallen out of the map?
    FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);
    if (!character.getPosition().intersects(level))
    {
        // Respawn character
        character.spawn(m_LM.getStartPosition(), GRAVITY);
    }

    // Loop through local blocks
    for (int x = startX; x < endX; x++)
    {
        for (int y = startY; y < endY; y++)
        {
            // Initialize the starting position of the current block
            block.left = x * TILE_SIZE;
            block.top = y * TILE_SIZE;

            // Has the character been burnt or drowned?
            // Use head (allowing character to sink a bit)
            if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
            {
                if (character.getHead().intersects(block))
                {
                    character.spawn(m_LM.getStartPosition(), GRAVITY);
                    if (m_ArrayLevel[y][x] == 2)
                    {
                        // play sound for fire
                        m_SM.playFallInFire();
                    }
                    else
                    {
                        // play sound for water
                        m_SM.playFallInWater();
                    }
                }
            }

            // Is the character colliding with a regular block?
            if (m_ArrayLevel[y][x] == 1)
            {
                if (character.getRight().intersects(block))
                {
                    character.stopRight(block.left);
                }
                else if (character.getLeft().intersects(block))
                {
                    character.stopRight(block.left);
                }

                if (character.getFeet().intersects(block))
                {
                    character.stopFalling(block.top);
                }
                else if (character.getHead().intersects(block))
                {
                    character.stopJump();
                }
            }

            // Start a particle effect if the character's feet have touched fire or water
            // Make sure this is the first time we have detected this
            if (!m_PS.running())
            {
                if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
                {
                    if (character.getFeet().intersects(block))
                    {
                        // Position and start particle system
                        m_PS.emitParticles(character.getCenter());
                    }
                }
            }

            // Has the character reached the goal?
            if (m_ArrayLevel[y][x] == 4)
            {
                reachedGoal = true;
            }
        }
    }
    return reachedGoal;
}