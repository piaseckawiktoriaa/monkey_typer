#include "Konfiguracje.h"
#include <fstream>

void Konfiguracje::wczytajZPliku(const std::string& config) {
    std::ifstream plik(config);
    std::string linia;
    while (std::getline(plik, linia)) {
        if (linia.starts_with("speed")) predkoscStartowa = std::stof(linia.substr(linia.find("=") + 1));
        else if (linia.starts_with("spawn")) interwalSpawnu = std::stof(linia.substr(linia.find("=") + 1));
        else if (linia.starts_with("round")) limitCzasu = std::stoi(linia.substr(linia.find("=") + 1));
        else if (linia.starts_with("font")) sciezkaCzcionki = linia.substr(linia.find("=") + 1);
    }
}