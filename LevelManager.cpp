#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelManager.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

int** LevelManager::nextLevel(VertexArray& rVaLevel)
{
    m_LevelSize.x = 0;
    m_LevelSize.y = 0;

    // Get next level
    m_CurrentLevel++;
    if (m_CurrentLevel > NUM_LEVELS)
    {
        m_CurrentLevel = 1;
        m_TimeModifier -= .1f;
    }

    // Load level from file
    string levelToLoad = "levels/level" + to_string(m_CurrentLevel) + ".txt";
    switch (m_CurrentLevel)
    {
        case 1:
            m_StartPosition.x = 100;
            m_StartPosition.y = 100;
            m_BaseTimeLimit = 30.0f;
            break;

        case 2:
            m_StartPosition.x = 100;
            m_StartPosition.y = 3600;
            m_BaseTimeLimit = 100.0f;
            break;

        case 3:
            m_StartPosition.x = 1250;
            m_StartPosition.y = 0;
            m_BaseTimeLimit = 30.0f;
            break;

        case 4:
            m_StartPosition.x = 50;
            m_StartPosition.y = 200;
            m_BaseTimeLimit = 50.0f;
            break;
    }
    ifstream inputFile(levelToLoad);
    string s;
    // Count number of rows in file
    while (getline(inputFile, s))
    {
        ++m_LevelSize.y;
    }
    // Store length of rows
    m_LevelSize.x = s.length();

    // Go back to start of file
    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    // Prepare 2D array to hold int values from file
    int** arrayLevel = new int*[m_LevelSize.y];
    for (int i = 0; i < m_LevelSize.y; i++)
    {
        // Add a new array into each array element
        arrayLevel[i] = new int[m_LevelSize.x];
    }

    // Loop through file and store all the values in the 2D array
    string row;
    int y = 0;
    while (inputFile >> row)
    {
        for (int x = 0; x < row.length(); x++)
        {
            const char val = row[x];
            arrayLevel[y][x] = atoi(&val);
        }
        y++;
    }
    inputFile.close();

    // What type of primitive are we using?
    rVaLevel.setPrimitiveType(Quads);
    // Set size of vertex array
    rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);
    // Start at beginning of vertex array
    int currentVertex = 0;
    for (int x = 0; x < m_LevelSize.x; x++)
    {
        for (int y = 0; y < m_LevelSize.y; y++)
        {
            // Position each vertex in the current quad
            rVaLevel[currentVertex + 0].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);
            rVaLevel[currentVertex + 1].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);
            rVaLevel[currentVertex + 2].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, (y* TILE_SIZE) + TILE_SIZE);
            rVaLevel[currentVertex + 3].position = Vector2f(x * TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

            // Which tile from the sprite sheet should we use?
            int verticalOffset = arrayLevel[x][y] * TILE_SIZE;

            rVaLevel[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
            rVaLevel[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
            rVaLevel[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
            rVaLevel[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

            // Position for next 4 vertices
            currentVertex = currentVertex + VERTS_IN_QUAD;
        }
    }

    return arrayLevel;
} // end NextLevel function

Vector2i LevelManager::getLevelSize()
{
    return m_LevelSize;
}

int LevelManager::getCurrentLevel()
{
    return m_CurrentLevel;
}

float LevelManager::getTimeLimit()
{
    return m_BaseTimeLimit * m_TimeModifier;
}

Vector2f LevelManager::getStartPosition()
{
    return m_StartPosition;
}