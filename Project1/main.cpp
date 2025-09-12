#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1024u, 768u }), "Windows XP Simulator");
    window.setFramerateLimit(60);

    // Carregando Texturas
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png"))
        return -1;

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("button.png"))
        return -1;

    sf::Sprite backgroundSprite(backgroundTexture);

    // Redimensionar a textura
    backgroundSprite.setScale(
        sf::Vector2f(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        )
    );
    backgroundSprite.setPosition({ 0.f,0.f });

    // Fonte
    sf::Font font("arial.ttf");

    float xpsize = 64.f;

    // --- Botão 1 ---
    sf::Sprite buttonSprite1(buttonTexture);
    sf::Vector2u buttonSize = buttonTexture.getSize();
    float scalex = xpsize / buttonSize.x;
    float scaley = xpsize / buttonSize.y;
    buttonSprite1.setScale({ scalex, scaley });
    buttonSprite1.setPosition({ 50.f, 50.f });

    sf::Text text1(font);
    text1.setString("Minecraft.exe");
    text1.setCharacterSize(16);
    sf::FloatRect iconBounds1 = buttonSprite1.getGlobalBounds();
    sf::FloatRect textBounds1 = text1.getLocalBounds();
    text1.setOrigin(sf::Vector2f(textBounds1.size.x / 2.f, 0.f));
    text1.setPosition(sf::Vector2f(
        iconBounds1.position.x + iconBounds1.size.x / 2.f,
        iconBounds1.position.y + iconBounds1.size.y + 5.f
    ));

    // --- Botão 2 ---
    sf::Sprite buttonSprite2(buttonTexture);
    buttonSprite2.setScale({ scalex, scaley });
    buttonSprite2.setPosition({ 150.f, 50.f });

    sf::Text text2(font);
    text2.setString("Chrome.exe");
    text2.setCharacterSize(16);
    sf::FloatRect iconBounds2 = buttonSprite2.getGlobalBounds();
    sf::FloatRect textBounds2 = text2.getLocalBounds();
    text2.setOrigin(sf::Vector2f(textBounds2.size.x / 2.f, 0.f));
    text2.setPosition(sf::Vector2f(
        iconBounds2.position.x + iconBounds2.size.x / 2.f,
        iconBounds2.position.y + iconBounds2.size.y + 5.f
    ));

    // --- Botão 3 ---
    sf::Sprite buttonSprite3(buttonTexture);
    buttonSprite3.setScale({ scalex, scaley });
    buttonSprite3.setPosition({ 250.f, 50.f });

    sf::Text text3(font);
    text3.setString("Word.exe");
    text3.setCharacterSize(16);
    sf::FloatRect iconBounds3 = buttonSprite3.getGlobalBounds();
    sf::FloatRect textBounds3 = text3.getLocalBounds();
    text3.setOrigin(sf::Vector2f(textBounds3.size.x / 2.f, 0.f));
    text3.setPosition(sf::Vector2f(
        iconBounds3.position.x + iconBounds3.size.x / 2.f,
        iconBounds3.position.y + iconBounds3.size.y + 5.f
    ));

    // --- Botão 4 ---
    sf::Sprite buttonSprite4(buttonTexture);
    buttonSprite4.setScale({ scalex, scaley });
    buttonSprite4.setPosition({ 350.f, 50.f });

    sf::Text text4(font);
    text4.setString("Excel.exe");
    text4.setCharacterSize(16);
    sf::FloatRect iconBounds4 = buttonSprite4.getGlobalBounds();
    sf::FloatRect textBounds4 = text4.getLocalBounds();
    text4.setOrigin(sf::Vector2f(textBounds4.size.x / 2.f, 0.f));
    text4.setPosition(sf::Vector2f(
        iconBounds4.position.x + iconBounds4.size.x / 2.f,
        iconBounds4.position.y + iconBounds4.size.y + 5.f
    ));

    // --- Botão 5 ---
    sf::Sprite buttonSprite5(buttonTexture);
    buttonSprite5.setScale({ scalex, scaley });
    buttonSprite5.setPosition({ 450.f, 50.f });

    sf::Text text5(font);
    text5.setString("Paint.exe");
    text5.setCharacterSize(16);
    sf::FloatRect iconBounds5 = buttonSprite5.getGlobalBounds();
    sf::FloatRect textBounds5 = text5.getLocalBounds();
    text5.setOrigin(sf::Vector2f(textBounds5.size.x / 2.f, 0.f));
    text5.setPosition(sf::Vector2f(
        iconBounds5.position.x + iconBounds5.size.x / 2.f,
        iconBounds5.position.y + iconBounds5.size.y + 5.f
    ));

    // Loop principal
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        window.draw(buttonSprite1); window.draw(text1);
        window.draw(buttonSprite2); window.draw(text2);
        window.draw(buttonSprite3); window.draw(text3);
        window.draw(buttonSprite4); window.draw(text4);
        window.draw(buttonSprite5); window.draw(text5);
        window.display();
    }

    return 0;
}
