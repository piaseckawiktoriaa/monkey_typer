#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow& okno)
    : okno_(okno), pokazInstrukcje_(false), rozpocznijGre_(false) {

    if (!czcionka_.loadFromFile("dane/czcionki/OpenSans-Bold.ttf")) {
        std::cerr << "Nie wczytano czcionki!\n";
    }

    if (!tloTekstura_.loadFromFile("dane/malpeczka.jpg")) {
        std::cerr << "Nie wczytano tła!\n";
    }

    tloSprite_.setTexture(tloTekstura_);
    tloSprite_.setScale(
        okno_.getSize().x / tloSprite_.getLocalBounds().width,
        okno_.getSize().y / tloSprite_.getLocalBounds().height
    );

    przyciskStart_.setSize(sf::Vector2f(300, 50));
    przyciskStart_.setFillColor(sf::Color(255, 105, 180));
    przyciskStart_.setPosition(okno_.getSize().x / 2 - 150, 400);

    tekstStart_.setFont(czcionka_);
    tekstStart_.setString("Zacznij gre");
    tekstStart_.setCharacterSize(28);
    tekstStart_.setFillColor(sf::Color::White);
    tekstStart_.setPosition(okno_.getSize().x / 2 - 80, 410);

    przyciskInstrukcje_.setSize(sf::Vector2f(300, 50));
    przyciskInstrukcje_.setFillColor(sf::Color(255, 105, 180));
    przyciskInstrukcje_.setPosition(okno_.getSize().x / 2 - 150, 470);

    tekstInstrukcje_.setFont(czcionka_);
    tekstInstrukcje_.setString("Instrukcje");
    tekstInstrukcje_.setCharacterSize(28);
    tekstInstrukcje_.setFillColor(sf::Color::White);
    tekstInstrukcje_.setPosition(okno_.getSize().x / 2 - 75, 480);
}

void Menu::obsluzZdarzenia(const sf::Event& e) {
    if (e.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f pos = okno_.mapPixelToCoords(sf::Mouse::getPosition(okno_));
        if (przyciskStart_.getGlobalBounds().contains(pos)) {
            rozpocznijGre_ = true;
        } else if (przyciskInstrukcje_.getGlobalBounds().contains(pos)) {
            pokazInstrukcje_ = true;
        }
    }
}

void Menu::rysuj() {
    sf::Vector2f mysz = okno_.mapPixelToCoords(sf::Mouse::getPosition(okno_));

    if (przyciskStart_.getGlobalBounds().contains(mysz))
        przyciskStart_.setFillColor(sf::Color(255, 150, 180));
    else
        przyciskStart_.setFillColor(sf::Color(255, 192, 203));

    if (przyciskInstrukcje_.getGlobalBounds().contains(mysz))
        przyciskInstrukcje_.setFillColor(sf::Color(255, 140, 170));
    else
        przyciskInstrukcje_.setFillColor(sf::Color(255, 182, 193));

    okno_.draw(tloSprite_);
    okno_.draw(przyciskStart_);
    okno_.draw(tekstStart_);
    okno_.draw(przyciskInstrukcje_);
    okno_.draw(tekstInstrukcje_);
}

bool Menu::czyPokazInstrukcje() const {
    return pokazInstrukcje_;
}

bool Menu::czyStartGry() const {
    return rozpocznijGre_;
}

sf::Font& Menu::getCzcionka() {
    return czcionka_;
}

void Menu::resetuj() {
    rozpocznijGre_ = false;
    pokazInstrukcje_ = false;
}
