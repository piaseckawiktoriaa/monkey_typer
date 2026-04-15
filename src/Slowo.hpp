
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Slowo {
public:
    Slowo(const std::string& tekst, const sf::Font& czcionka, float y, float predkosc);

    void aktualizuj(float dt);
    void rysuj(sf::RenderWindow& okno);
    bool pozaEkranem() const;

    bool sprawdzBufor(const std::string& bufor);
    void aktualizujKolorGradientu(const std::string& bufor);

    std::string tekst;

private:
    std::vector<sf::Text> litery;
    float predkosc;
};
