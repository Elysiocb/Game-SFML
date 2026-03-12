#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <list> // (Vamos precisar disso para o "pré-carregamento")

// O Animator AGORA "É UM" sf::Sprite
class Animator : public sf::Sprite { 
private:
    // --- DADOS INTERNOS (O que a classe esconde) ---

    // 1. Armazenamento de PNGs (O "Pré-Carregamento")
    //    Para evitar carregar do disco 60x por segundo
    std::list<sf::Texture> m_textureStorage;

    // 2. A "Receita" de UMA Animação (Seu "animClip")
    struct AnimationClip {
        std::vector<sf::Texture*> frames; // A lista de PNGs pré-carregados
        sf::Time baseFrameTime;           // O "tempo de espera"
        bool loop;
    };

    // 3. O "Catálogo" de todas as "Receitas"
    //    (Guarda "attack", "idle", "run", etc.)
    std::map<std::string, AnimationClip> m_animations;


    // --- VARIÁVEIS DE ESTADO (O que está acontecendo agora) ---

    // A sua lógica do "Modo Manual", agora dentro da classe!
    sf::Clock m_clock;      // O cronômetro (para o seu "elapsedTime")
    sf::Time m_elapsedTime;   // O acumulador de tempo

    float m_speedMultiplier;  // Para "rápido", "normal", "lento"
    AnimationClip* m_currentClip; // A "receita" tocando agora
    int m_currentFrame;           // O seu "index"

public:
    // --- BOTÕES PÚBLICOS (O que o main.cpp pode usar) ---

    // Construtor: Exige uma textura "placeholder" (temporária)
    // para resolver o problema do construtor do sf::Sprite
    Animator(const sf::Texture& placeholderTexture);

    // Torna os métodos setScale da classe base (sf::Sprite) visíveis.
    //using sf::Sprite::setScale;//SE ESSA LINHA NAO RESOLVER DELETA ESSA PORRA

    // "Ensina" uma nova receita (lista de PNGs) para o Animator
    void loadAnimation(
        const std::string& name,                   // ex: "attack"
        const std::vector<std::string>& filenames, // ex: {"f1.png", "f2.png"}
        sf::Time frameTime,
        bool loop
    );

    // Seu "play(AnimClip, frame)"
    void play(const std::string& name, int startFrame = 0);

    // Seu "stop(AnimClip)" (simplificado)
    void stop();

    // Seu "setVelocity(velocity)"
    void setSpeed(const std::string& speed); // "rápido", "normal", "lento"

    // O "Motor" - A sua lógica do "loop com index"
    // (Não precisa de 'dt', pois usaremos nosso m_clock interno)
    void update();

};