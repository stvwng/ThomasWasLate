#include "Engine.h"

Engine::Engine()
{
    // Get screen resolution and create SFML window and view
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    m_Window.create(
        VideoMode(resolution.x, resolution.y),
        "Thomas Was Late",
        Style::Fullscreen
    );

    // Initialize full screen view
    m_MainView.setSize(resolution);
    m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

    // Initialize split screen views
    m_LeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
    m_RightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
    m_BGLeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
    m_BGRightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
    
    m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");
    m_BackgroundSprite.setTexture(m_BackgroundTexture);
}

void Engine::run()
{
    Clock clock;

    while (m_Window.isOpen())
    {
        Time dt = clock.restart();
        m_GameTimeTotal += dt;
        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}
