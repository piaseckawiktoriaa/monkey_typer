#include "Instrukcje.h"
#include <iostream>

Instrukcje::Instrukcje(sf::RenderWindow& okno, const sf::Font& czcionka)
    : okno_(okno), powrot_(false) {

    if (!tloTekstura_.loadFromFile("dane/tlogra.jpg")) {
        std::cerr << "Nie wczytano tla instrukcji!\n";
    }
    tloSprite_.setTexture(tloTekstura_);
    tloSprite_.setScale(
        okno_.getSize().x / tloSprite_.getLocalBounds().width,
        okno_.getSize().y / tloSprite_.getLocalBounds().height
    );

    tekst_.setFont(czcionka);
    tekst_.setCharacterSize(26);
    tekst_.setFillColor(sf::Color(255, 255, 255));
    tekst_.setString("Witaj w Monkey Typer! \n\n"
                     "Celem gry jest wpisywanie slow, zanim znikna!\n"
                     "0 ~ pauza\n"
                     "+ ~ przyspieszenie\n"
                     "- ~ spowolnienie\n\n"
                     "Zostan mistrzem gry, powodzenia!!!"
                     );
    tekst_.setPosition(60.f, 80.f);

    przycisk_.setSize({260, 60});
    przycisk_.setFillColor(sf::Color(255, 192, 203));
    przycisk_.setPosition(okno_.getSize().x / 2.f - 130.f, 430.f);
    przycisk_.setOutlineColor(sf::Color::White);
    przycisk_.setOutlineThickness(2);

    napisPrzycisku_.setFont(czcionka);
    napisPrzycisku_.setCharacterSize(28);
    napisPrzycisku_.setFillColor(sf::Color::White);
    napisPrzycisku_.setString("Powrot do menu");

    sf::FloatRect textBounds = napisPrzycisku_.getLocalBounds();
    napisPrzycisku_.setOrigin(textBounds.left + textBounds.width / 2.f,
                              textBounds.top + textBounds.height / 2.f);

    napisPrzycisku_.setPosition(
        przycisk_.getPosition().x + przycisk_.getSize().x / 2.f,
        przycisk_.getPosition().y + przycisk_.getSize().y / 2.f
    );

}

bool Instrukcje::czyPowrot() const {
    return powrot_;
}

void Instrukcje::wyswietl() {
    powrot_ = false;

    while (okno_.isOpen() && !powrot_) {
        sf::Event e;
        while (okno_.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                okno_.close();
            if (e.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f pos = okno_.mapPixelToCoords(sf::Mouse::getPosition(okno_));
                if (przycisk_.getGlobalBounds().contains(pos)) {
                    powrot_ = true;
                }
            }
        }

        sf::Vector2f mysz = okno_.mapPixelToCoords(sf::Mouse::getPosition(okno_));
        if (przycisk_.getGlobalBounds().contains(mysz))
            przycisk_.setFillColor(sf::Color(255, 150, 200));
        else
            przycisk_.setFillColor(sf::Color(255, 192, 203));

        okno_.clear();
        okno_.draw(tloSprite_);
        okno_.draw(tekst_);
        okno_.draw(przycisk_);
        okno_.draw(napisPrzycisku_);
        okno_.display();
    }
}
