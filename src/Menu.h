#pragma once
#include <SFML/Graphics.hpp>

class Menu {
    sf::RenderWindow& okno_;
    sf::Texture tloTekstura_;
    sf::Sprite tloSprite_;
    sf::Font czcionka_;
    sf::Text tytul_;

    sf::RectangleShape przyciskStart_, przyciskInstrukcje_;
    sf::Text tekstStart_, tekstInstrukcje_;

    bool pokazInstrukcje_;
    bool rozpocznijGre_;

public:
    Menu(sf::RenderWindow& okno);
    void rysuj();
    void obsluzZdarzenia(const sf::Event& e);
    bool czyPokazInstrukcje() const;
    bool czyStartGry() const;
    sf::Font& getCzcionka();
    void resetuj();
};
