#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <random>
#include <filesystem>
#include "Slowo.hpp"
#include "Konfiguracje.h"

struct Wynik {
    std::string nick;
    int trafione;
    int czas;
};
class Gra {
public:
    explicit Gra(sf::RenderWindow& okno);
    Gra(sf::RenderWindow& okno, const std::string& nick);

    void uruchom();

private:
    sf::RenderWindow& okno_;

    Konfiguracje konfiguracja_;
    std::vector<std::string> bazaSlow_;
    std::vector<Slowo> slowa_;

    sf::Font czcionkaInterfejsu_;
    std::vector<sf::Font> czcionkiSlow_;

    sf::Text tekstZycia_;
    sf::Text tekstCzasu_;
    sf::Text tekstKoniecGry_;
    sf::Text tekstPauzy_;

    sf::SoundBuffer buforDzwieku_;
    sf::Sound dzwiekTrafienia_;

    sf::Texture tloTekstura_;
    sf::Sprite tloSprite_;

    float zapisanyWPM_ = 0.f;

    std::string bufor_;

    int zycia_ = 5;
    int trafioneSlowa_ = 0;
    int trafioneZnaki_ = 0;

    float predkoscStartowa_ = 100.f;
    float interwalPojawiania_ = 3.f;
    float limitCzasu_ = 60.f;

    Slowo* aktywne_ = nullptr;

    std::mt19937 losownik_;

    sf::Clock zegarPojawiania_;
    sf::Clock zegarTrudnosci_;
    sf::Clock zegarKlatki_;
    sf::Clock stoper_;

    enum class StanGry { GRA, PAUZA, KONIEC };
    StanGry stanGry_ = StanGry::GRA;

    void rozpocznijNowaRozgrywke();
    void obsluzZdarzenia();
    void aktualizuj(float dt);
    void rysuj();

    void aktualizujZycia();
    void pokazStatystyki(const std::string& komunikat);

    sf::Clock zegarRundy_;
    std::string nick_;
    bool wynikZapisany_ = false;
    std::vector<Wynik> topWyniki_;

};

   




