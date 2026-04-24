#pragma once

#include <string>
#include <iostream>

#define KK sf::Keyboard::Key
#define KP sf::Event::KeyPressed
#define KR sf::Event::KeyReleased

using namespace std;

/**
 * @brief Utility functions for application initialization, path management, and asset loading.
 */

void p(string str);

string getPath();

void setWindowIcon(sf::RenderWindow& window, sf::Image iconImage);

void loadData(map<int, sf::Texture>& assetData_imagens);
