#include "ParticleSystem.h"
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;
using namespace std;

void ParticleSystem::init(int numParticles)
{
    m_Vertices.setPrimitiveType(Points);
    m_Vertices.resize(numParticles);

    // Create particles
    for (int i = 0; i < numParticles; i++)
    {
        srand(time(0) + 1);
        float angle = (rand() % 360) * 3.14f / 180.f;
        float speed = (rand() % 600) + 600.f;

        Vector2f direction;
        direction = Vector2f(cos(angle) * speed, sin(angle) * speed);

        m_Particles.push_back(Particle(direction));
    }
}

void ParticleSystem::update(float dt)
{
    m_Duration -= dt;
    vector<Particle>::iterator it;
    int currentVertex = 0;

    for (it = m_Particles.begin(); it != m_Particles.end(); it++)
    {
        // Move the particle
        it->update(dt);
        // Update the vertex array
        m_Vertices[currentVertex++].position = it->getPosition();
    }

    if (m_Duration < 0)
    {
        m_IsRunning = false;
    }
}

void ParticleSystem::emitParticles(Vector2f startPosition)
{
    m_IsRunning = true;
    m_Duration = 2;

    vector<Particle>::iterator it;
    int currentVertex = 0;

    for (it = m_Particles.begin(); it != m_Particles.end(); it++)
    {
        m_Vertices[currentVertex++].color = Color::Yellow;
        it->setPosition(startPosition);
    }
}

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_Vertices, states);
}

bool ParticleSystem::running()
{
    return m_IsRunning;
}