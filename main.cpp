#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Animator.hpp"
#include "MinhaBiblioteca.hpp"

int main() {
    // Configuração da janela
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My Final Stand", sf::Style::Resize);
    window.setFramerateLimit(60);

    // Constrói o caminho para a pasta de assets
    std::string assetsPath = getPath() + "/assets/images/";

    // Carrega uma textura temporária para inicializar o Animator
    sf::Texture texPlaceholder;
    if (!texPlaceholder.loadFromFile(assetsPath + "placeholder.png")) {
        p("Falha ao carregar o placeholder: " + assetsPath + "placeholder.png");
        return -1;
    }

    // Cria e posiciona o player
    Animator meuPlayer(texPlaceholder);
    meuPlayer.setPosition({100.f, 100.f});
    meuPlayer.setScale({0.5f, 0.5f});

    // Define os frames para a animação "piscar"
    std::vector<std::string> framesPiscando = {
        assetsPath + "enemy_1.png",
        assetsPath + "enemy_2.png",
        assetsPath + "enemy_3.png"
    };

    // Carrega e inicia a animação
    meuPlayer.loadAnimation("piscar", framesPiscando, sf::seconds(0.3f), true);
    meuPlayer.play("piscar");

    // Loop principal
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Atualiza a lógica do animator
        meuPlayer.update();

        // Desenha os objetos na tela
        window.clear(sf::Color::White);
        window.draw(meuPlayer);
        window.display();
    }
    return 0;
}