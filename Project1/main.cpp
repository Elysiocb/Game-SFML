#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "Exemplo SFML");
    window.setFramerateLimit(60);

    // Carregando Texturas
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png"))
        return -1;

    sf::Texture button;
    if (!button.loadFromFile("button.png"))
        return -1;

    sf::Sprite backgroundSprite(backgroundTexture);
    /*
    backgroundSprite.setOrigin(
        sf::Vector2f(backgroundTexture.getSize().x / 2.f,
                     backgroundTexture.getSize().y / 2.f)
    );*/

    /* Mostrar modos fullscreen disponíveis
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "
                  << mode.size.x << "x" << mode.size.y << " - "
                  << mode.bitsPerPixel << " bpp" << std::endl;
    }*/

    // Criar janela no tamanho desejado
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode({1024u, 768u}, desktop.bitsPerPixel), "Windows XP Simulator");

	//Redimensionar a textura
    backgroundSprite.setScale(
        sf::Vector2f(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        )
    );
    backgroundSprite.setPosition({ 0.f,0.f });

    // Loop principal
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>())
            {
                const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent && keyEvent->code == sf::Keyboard::Key::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        window.display();
    }

    return 0;
}
