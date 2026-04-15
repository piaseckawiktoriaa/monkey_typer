#pragma once
#include <SFML/Graphics.hpp>

class Instrukcje {
public:
    Instrukcje(sf::RenderWindow& okno, const sf::Font& czcionka);
    void wyswietl();
    bool czyPowrot() const;

private:
    sf::RenderWindow& okno_;
    sf::Text tekst_;
    sf::RectangleShape przycisk_;
    sf::Text napisPrzycisku_;

    sf::Texture tloTekstura_;
    sf::Sprite tloSprite_;

    bool powrot_ = false;
};

