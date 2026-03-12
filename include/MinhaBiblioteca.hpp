#pragma once

#include <string>
#include <iostream>

#define KK sf::Keyboard::Key
#define KP sf::Event::KeyPressed
#define KR sf::Event::KeyReleased

using namespace std;

// Função auxiliar para exibir informações no terminal.
void p(string str);

// Recupera, em tempo de execução, o caminho onde o executável do programa está.
string getPath();

// Define o ícone da aplicação.
void setWindowIcon(sf::RenderWindow& window, sf::Image iconImage);

// Carrega dados a partir dos conteúdos de mídia no diretório /assets.
void loadData(map<int, sf::Texture>& assetData_imagens);
