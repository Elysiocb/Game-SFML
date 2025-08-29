#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), "Exemplo SFML");

    sf::Texture texture;
    if (!texture.loadFromFile("foto1.jpeg"))
        return -1;

    sf::Sprite sprite(texture);

    // Centralizar a imagem
    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
    sprite.setPosition(sf::Vector2f(800.f / 2.f, 600.f / 2.f));

    // Display the list of all the video modes available for fullscreen
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "
            << mode.size.x << "x" << mode.size.y << " - "
            << mode.bitsPerPixel << " bpp" << std::endl;
    }

    // Create a window with the same pixel depth as the desktop
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode({ 1024, 768 }, desktop.bitsPerPixel), "SFML window");

    while (window.isOpen())
    {
        // Processar eventos para manter a janela responsiva
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())        // Fecha ao clicar no X
                window.close();

            if (event->is<sf::Event::KeyPressed>())   // Fecha ao apertar Esc
            {
                const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent && keyEvent->code == sf::Keyboard::Key::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
