#include <string>
#include <iostream>
#include <windows.h>
#include <map>
#include <SFML/Graphics.hpp>

using namespace std;

const map<int, string> assetName_imagens = {
    {1, "sfml-logo.png"},
    {2, "bg.png"},
    {3, "tx_bola.png"}
};

// Implementação da função auxiliar para exibir textos no terminal.
void p(string str){
    std::cout << str << std::endl;
}

// Recupera, em tempo de execução, o caminho onde o executável do programa está.
string getPath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    wstring ws(buffer); // Converte para wideString.
    string str(ws.begin(), ws.end()); // Converte para string.
    string::size_type pos = string(str).find_last_of("\\/"); // Localiza último par de barras no caminho completo.
    return string(str).substr(0, pos); // Remove nome do executável ao final do caminho completo e retorna como string.
}

void setWindowIcon(sf::RenderWindow& window, sf::Image iconImage) {
    window.setIcon(iconImage.getSize(), iconImage.getPixelsPtr());
}

void loadData(map<int, sf::Texture>& assetData_imagens) {
    // Carrega texturas.
    for(const auto& item : assetName_imagens) {
        sf::Texture imageTemp;
        if(imageTemp.loadFromFile(getPath() + "/assets/images/" + item.second)){
            assetData_imagens[item.first] = imageTemp;
        } else {
            p("Erro ao carregar imagem " + item.second + "!");
        }
    }
    p("Texturas carregadas com sucesso!");
}
