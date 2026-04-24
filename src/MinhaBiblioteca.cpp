#include <string>
#include <iostream>
#include <windows.h>
#include <map>
#include <SFML/Graphics.hpp>

using namespace std;

/**
 * @brief Implementation of utility functions for path handling, window configuration, and asset management.
 */

const map<int, string> assetName_imagens = {
    {1, "sfml-logo.png"},
    {2, "bg.png"},
    {3, "tx_bola.png"}
};

void p(string str){
    std::cout << str << std::endl;
}

string getPath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    wstring ws(buffer); 
    string str(ws.begin(), ws.end()); 
    string::size_type pos = string(str).find_last_of("\\/"); 
    return string(str).substr(0, pos); 
}

void setWindowIcon(sf::RenderWindow& window, sf::Image iconImage) {
    window.setIcon(iconImage.getSize(), iconImage.getPixelsPtr());
}

void loadData(map<int, sf::Texture>& assetData_imagens) {
    for(const auto& item : assetName_imagens) {
        sf::Texture imageTemp;
        if(imageTemp.loadFromFile(getPath() + "/assets/images/" + item.second)){
            assetData_imagens[item.first] = imageTemp;
        } else {
            p("Error loading image " + item.second + "!");
        }
    }
    p("Textures loaded successfully!");
}
