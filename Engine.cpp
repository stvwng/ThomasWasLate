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

    // Can the graphics card use shaders?
    if (!sf::Shader::isAvailable())
    {
        m_Window.close();
    }
    else
    {
        // Load 2 shaders (1 vertex, 1 fragment)
        m_RippleShader.loadFromFile("shaders/rippleShader.vert", "shaders/RippleShader.frag");
    }
    
    m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");
    m_BackgroundSprite.setTexture(m_BackgroundTexture);

    // Load texture for background vertex array
    m_TextureTiles = TextureHolder::GetTexture("graphics/tiles_sheet.png");

    // Initialize particle system
    m_PS.init(1000);
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
