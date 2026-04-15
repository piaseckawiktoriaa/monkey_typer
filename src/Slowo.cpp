
#include "Slowo.hpp"
#include <random>

Slowo::Slowo(const std::string& tekst, const sf::Font& czcionka, float y, float predkosc)
    : tekst(tekst), predkosc(predkosc) {

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rozmiarLosowy(30, 65);
    int rozmiar = rozmiarLosowy(gen);

    float x = 800.f;
    for (char znak : tekst) {
        sf::Text litera;
        litera.setFont(czcionka);
        litera.setCharacterSize(rozmiar);
        litera.setString(znak);
        litera.setFillColor(sf::Color::White);
        litera.setPosition(x, y);
        x += litera.getGlobalBounds().width + 4.f;
        litery.push_back(litera);
    }
}

void Slowo::aktualizuj(float dt) {
    for (auto& l : litery)
        l.move(-predkosc * dt, 0.f);
}

void Slowo::rysuj(sf::RenderWindow& okno) {
    for (auto& l : litery)
        okno.draw(l);
}

bool Slowo::pozaEkranem() const {
    return litery.empty() || (litery.back().getPosition().x < -10.f);
}

bool Slowo::sprawdzBufor(const std::string& bufor) {
    if (bufor.empty() || bufor.size() > tekst.size())
        return false;

    for (std::size_t i = 0; i < bufor.size(); ++i) {
        if (std::tolower(bufor[i]) != std::tolower(tekst[i])) return false;
    }

    for (std::size_t i = 0; i < tekst.size(); ++i) {
        if (i < bufor.size()) {
            float t = static_cast<float>(i) / std::max(1.f, static_cast<float>(bufor.size() - 1));
            sf::Color kolor(
                static_cast<sf::Uint8>((1 - t) * 100 + t * 0),
                static_cast<sf::Uint8>((1 - t) * 200 + t * 255),
                static_cast<sf::Uint8>((1 - t) * 100 + t * 0)
            );
            litery[i].setFillColor(kolor);
        } else {
            litery[i].setFillColor(sf::Color::White);
        }
    }

    return bufor.size() == tekst.size();
}

void Slowo::aktualizujKolorGradientu(const std::string& bufor) {
    if (litery.empty()) return;
    std::size_t ile = std::min(bufor.size(), tekst.size());
    for (std::size_t i = 0; i < tekst.size(); ++i) {
        if (i < ile) {
            float t = static_cast<float>(i) / std::max(1.f, static_cast<float>(ile - 1));
            sf::Color kolor(
                static_cast<sf::Uint8>((1 - t) * 100 + t * 0),
                static_cast<sf::Uint8>((1 - t) * 200 + t * 255),
                static_cast<sf::Uint8>((1 - t) * 100 + t * 0)
            );
            litery[i].setFillColor(kolor);
        } else {
            litery[i].setFillColor(sf::Color::White);
        }
    }
    bool prefixNiePasuje = false;
    for (std::size_t i = 0; i < bufor.size() && i < tekst.size(); ++i) {
        if (tekst[i] != bufor[i]) {
            prefixNiePasuje = true;
            litery[i].setFillColor(sf::Color::Red);
            break;
        }
    }

    if (!prefixNiePasuje) {
        for (std::size_t i = 0; i < bufor.size() && i < tekst.size(); ++i) {
            float t = static_cast<float>(i) / std::max(1.f, static_cast<float>(bufor.size() - 1));
            sf::Color kolor(
                static_cast<sf::Uint8>((1 - t) * 100 + t * 0),
                static_cast<sf::Uint8>((1 - t) * 200 + t * 255),
                static_cast<sf::Uint8>((1 - t) * 100 + t * 0)
            );
            litery[i].setFillColor(kolor);
        }
    }
}
