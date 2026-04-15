#include "Gra.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <iostream>
#include <filesystem>

Gra::Gra(sf::RenderWindow& okno, const std::string& nick)
    : Gra(okno) {
    nick_ = nick;
}

Gra::Gra(sf::RenderWindow& okno)
    : okno_(okno), losownik_(std::random_device{}()), stanGry_(StanGry::GRA), wynikZapisany_(false) {
    konfiguracja_.wczytajZPliku("dane/config.txt");

    predkoscStartowa_ = konfiguracja_.predkoscStartowa;
    interwalPojawiania_ = konfiguracja_.interwalSpawnu;
    limitCzasu_ = konfiguracja_.limitCzasu;

    if (!czcionkaInterfejsu_.loadFromFile("dane/czcionki/DejaVuSans.ttf")) {
        std::cerr << "Nie mozna wczytac czcionki interfejsu!\n";
    }

    for (const auto& plik : std::filesystem::directory_iterator("dane/czcionki")) {
        if (plik.path().filename() == "DejaVuSans.ttf") continue;
        sf::Font czcionka;
        if (czcionka.loadFromFile(plik.path().string())) {
            czcionkiSlow_.push_back(czcionka);
        }
    }

    if (!buforDzwieku_.loadFromFile("dane/ding.wav")) {
        std::cerr << "Nie udalo sie wczytac dzwieku!\n";
    }
    dzwiekTrafienia_.setBuffer(buforDzwieku_);

    tekstZycia_.setFont(czcionkaInterfejsu_);
    tekstZycia_.setCharacterSize(28);
    tekstZycia_.setFillColor(sf::Color::Red);
    tekstZycia_.setPosition(10.f, 10.f);

    tekstPauzy_.setFont(czcionkaInterfejsu_);
    tekstPauzy_.setCharacterSize(48);
    tekstPauzy_.setFillColor(sf::Color::Cyan);
    tekstPauzy_.setString("PAUZA (0)");
    sf::FloatRect bounds = tekstPauzy_.getLocalBounds();
    tekstPauzy_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    tekstPauzy_.setPosition(
        static_cast<float>(okno_.getSize().x) / 2.f,
        static_cast<float>(okno_.getSize().y) / 2.f
        );

    tekstCzasu_.setFont(czcionkaInterfejsu_);
    tekstCzasu_.setCharacterSize(24);
    tekstCzasu_.setFillColor(sf::Color::White);
    tekstCzasu_.setPosition(650.f, 10.f);

    std::ifstream plik("dane/words.txt");
    std::string linia;
    while (std::getline(plik, linia)) {
        if (!linia.empty()) bazaSlow_.push_back(linia);
    }

    rozpocznijNowaRozgrywke();

    if (!tloTekstura_.loadFromFile("dane/tlogra.jpg")) {
        std::cerr << "Nie wczytano tla gry z dane/tlogra.jpg!\n";
    }
    tloSprite_.setTexture(tloTekstura_);

    float scaleX = okno_.getSize().x / tloSprite_.getLocalBounds().width;
    float scaleY = okno_.getSize().y / tloSprite_.getLocalBounds().height;
    tloSprite_.setScale(scaleX, scaleY);
}

void Gra::pokazStatystyki(const std::string& komunikat) {
    float sek = stoper_.getElapsedTime().asSeconds();
    float wpm = (trafioneZnaki_ / 5.f) / (sek / 60.f);
    std::ostringstream oss;
    oss << komunikat << "\nSlowa: " << trafioneSlowa_
        << "\nWPM: " << std::fixed << std::setprecision(1) << wpm
        << "\n\n[Enter] restart\n[Esc] wyjdz";
    tekstKoniecGry_.setString(oss.str());

    zapisanyWPM_ = wpm;

    if (!wynikZapisany_) {
        int sekundy = static_cast<int>(sek);
        std::ofstream plik("dane/wyniki.txt", std::ios::app);
        if (plik) {
            plik << nick_ << ";" << trafioneSlowa_ << ";" << sekundy << "\n";
        } else {
            std::cerr << "Nie mozna otworzyc pliku wynikow do zapisu!\n";
        }

        std::ifstream odczyt("dane/wyniki.txt");
        std::string linia;
        topWyniki_.clear();

        while (std::getline(odczyt, linia)) {
            size_t pos1 = linia.find(';');
            size_t pos2 = linia.rfind(';');
            if (pos1 != std::string::npos && pos2 != std::string::npos && pos1 != pos2) {
                std::string n = linia.substr(0, pos1);
                int t = std::stoi(linia.substr(pos1 + 1, pos2 - pos1 - 1));
                int c = std::stoi(linia.substr(pos2 + 1));
                topWyniki_.push_back({n, t, c});
            }
        }

        std::sort(topWyniki_.begin(), topWyniki_.end(), [](const Wynik& a, const Wynik& b) {
            return a.trafione > b.trafione || (a.trafione == b.trafione && a.czas < b.czas);
        });

        wynikZapisany_ = true;
    }
}

void Gra::rozpocznijNowaRozgrywke() {
    slowa_.clear();
    bufor_.clear();
    aktywne_ = nullptr;
    zycia_ = 5;
    trafioneSlowa_ = 0;
    trafioneZnaki_ = 0;
    predkoscStartowa_ = konfiguracja_.predkoscStartowa;
    interwalPojawiania_ = konfiguracja_.interwalSpawnu;
    zegarPojawiania_.restart();
    zegarTrudnosci_.restart();
    zegarKlatki_.restart();
    zegarRundy_.restart();
    stoper_.restart();
    stanGry_ = StanGry::GRA;
    aktualizujZycia();
}

void Gra::aktualizujZycia() {
    sf::String serduszka;
    for (int i = 0; i < zycia_; ++i)
        serduszka += static_cast<sf::Uint32>(0x2665);
    tekstZycia_.setString(serduszka);
}

void Gra::uruchom() {
    while (okno_.isOpen()) {
        obsluzZdarzenia();
        if (stanGry_ == StanGry::GRA)
            aktualizuj(zegarKlatki_.restart().asSeconds());
        rysuj();
    }
}

void Gra::obsluzZdarzenia() {
    sf::Event e;
    while (okno_.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            okno_.close();

        if (stanGry_ == StanGry::KONIEC && e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Enter) rozpocznijNowaRozgrywke();
            if (e.key.code == sf::Keyboard::Escape) okno_.close();
        }

        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Num0) {
            if (stanGry_ == StanGry::GRA) stanGry_ = StanGry::PAUZA;
            else if (stanGry_ == StanGry::PAUZA) stanGry_ = StanGry::GRA;
        }

        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Add || e.key.code == sf::Keyboard::Equal) {
                predkoscStartowa_ += 10.f;
            } else if (e.key.code == sf::Keyboard::Hyphen || e.key.code == sf::Keyboard::Subtract) {
                predkoscStartowa_ = std::max(10.f, predkoscStartowa_ - 10.f);
            }
        }


        if (stanGry_ == StanGry::GRA && e.type == sf::Event::TextEntered) {
            if (!aktywne_) return;

            sf::Uint32 unicode = e.text.unicode;
            if (unicode == 8 && !bufor_.empty()) {
                bufor_.pop_back();
                aktywne_->aktualizujKolorGradientu(bufor_);
                return;
            }

            if (unicode < 128 && std::isalpha(static_cast<unsigned char>(unicode))) {
                char znak = static_cast<char>(std::tolower(static_cast<unsigned char>(unicode)));
                bufor_ += znak;

                if (aktywne_->sprawdzBufor(bufor_)) {
                    trafioneSlowa_++;
                    trafioneZnaki_ += aktywne_->tekst.size();
                    dzwiekTrafienia_.play();

                    std::string tekstDoUsuniecia = aktywne_->tekst;
                    slowa_.erase(std::remove_if(slowa_.begin(), slowa_.end(),
                        [&](const Slowo& s) {
                            return s.tekst == tekstDoUsuniecia;
                        }), slowa_.end());

                    aktywne_ = slowa_.empty() ? nullptr : &slowa_.front();
                    bufor_.clear();
                } else {
                    aktywne_->aktualizujKolorGradientu(bufor_);
                }
            }
        }

    }
}

void Gra::aktualizuj(float dt) {
    if (zegarTrudnosci_.getElapsedTime().asSeconds() > 10.f) {
        predkoscStartowa_ += 10.f;
        interwalPojawiania_ = std::max(1.f, interwalPojawiania_ - 0.1f);
        zegarTrudnosci_.restart();
    }

    if (zegarPojawiania_.getElapsedTime().asSeconds() > interwalPojawiania_) {
        std::uniform_int_distribution<size_t> wyborSlow(0, bazaSlow_.size() - 1);
        std::uniform_real_distribution<float> pozycjaY(50.f, 550.f);
        const auto& slowo = bazaSlow_[wyborSlow(losownik_)];
        float y = pozycjaY(losownik_);
        const auto& czcionka = czcionkiSlow_[losownik_() % czcionkiSlow_.size()];
        slowa_.emplace_back(slowo, czcionka, y, predkoscStartowa_);
        zegarPojawiania_.restart();
        if (!aktywne_) {
            aktywne_ = &slowa_.back();
            bufor_.clear();
        }
    }

    for (auto& s : slowa_) s.aktualizuj(dt);

    for (auto it = slowa_.begin(); it != slowa_.end();) {
        if (it->pozaEkranem()) {
            if (aktywne_ == &(*it)) {
                bufor_.clear();
                aktywne_ = nullptr;
            }
            it = slowa_.erase(it);
            zycia_--;
            aktualizujZycia();

            if (zycia_ <= 0) {
                stanGry_ = StanGry::KONIEC;
                slowa_.clear();
                pokazStatystyki("PRZEGRANA!");
                return;
            }
        } else ++it;
    }

    if (!slowa_.empty()) {
        aktywne_ = &slowa_.front();
        if (aktywne_) aktywne_->aktualizujKolorGradientu(bufor_);
    } else {
        aktywne_ = nullptr;
    }

    float uplynelo = stoper_.getElapsedTime().asSeconds();
    if (uplynelo >= limitCzasu_) {
        stanGry_ = StanGry::KONIEC;
        slowa_.clear();
        pokazStatystyki("WYGRANA!");
        return;
    }

    int pozostale = static_cast<int>(std::max(0.f, limitCzasu_ - uplynelo));
    int minuty = pozostale / 60;
    int sekundy = pozostale % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minuty << ":"
        << std::setw(2) << sekundy;
    tekstCzasu_.setString(oss.str());
}

void Gra::rysuj() {
    okno_.clear();
    okno_.draw(tloSprite_);

    for (auto& s : slowa_) s.rysuj(okno_);
    okno_.draw(tekstZycia_);
    okno_.draw(tekstCzasu_);
    if (stanGry_ == StanGry::PAUZA) okno_.draw(tekstPauzy_);
    if (stanGry_ == StanGry::KONIEC) okno_.draw(tekstKoniecGry_);
    if (stanGry_ == StanGry::KONIEC) {

    float sek = stoper_.getElapsedTime().asSeconds();
    float wpm = zapisanyWPM_;

    float szerokosc = 360.f;
    float wysokosc = 300.f;
    float lacznaSzerokosc = szerokosc * 2 + 2.f; // 2 to separator
    float startX = (okno_.getSize().x - lacznaSzerokosc) / 2.f;

    sf::RectangleShape tloLewo(sf::Vector2f(szerokosc, wysokosc));
    tloLewo.setPosition(startX, 100);
    tloLewo.setFillColor(sf::Color(0, 0, 0, 150));
    okno_.draw(tloLewo);

    sf::RectangleShape tloPrawo(sf::Vector2f(szerokosc, wysokosc));
    tloPrawo.setPosition(startX + szerokosc + 2, 100);
    tloPrawo.setFillColor(sf::Color(0, 0, 0, 150));
    okno_.draw(tloPrawo);

    sf::RectangleShape separator(sf::Vector2f(2, wysokosc + 20));
    separator.setPosition(startX + szerokosc, 90);
    separator.setFillColor(sf::Color(255, 255, 255, 100));
    okno_.draw(separator);

    std::ostringstream wynikStr;
    wynikStr << (zycia_ > 0 ? "WYGRANA!" : "PRZEGRANA!") << "\n\n"
             << "Nick: " << nick_ << "\n"
             << "Slowa: " << trafioneSlowa_ << "\n"
             << "WPM: " << std::fixed << std::setprecision(1) << wpm << "\n\n"
             << "[Enter] restart\n[Esc] wyjscie";

    sf::Text wynikTekst;
    wynikTekst.setFont(czcionkaInterfejsu_);
    wynikTekst.setCharacterSize(24);
    wynikTekst.setFillColor(zycia_ > 0 ? sf::Color::Green : sf::Color::Red);
    wynikTekst.setString(wynikStr.str());
    wynikTekst.setPosition(70, 120);
    okno_.draw(wynikTekst);

    sf::Text naglowek("TOP 5 wynikow:", czcionkaInterfejsu_, 24);
    naglowek.setFillColor(sf::Color(255, 105, 180));
    naglowek.setPosition(450, 120);
    okno_.draw(naglowek);

    for (int i = 0; i < std::min(5, (int)topWyniki_.size()); ++i) {
        const auto& w = topWyniki_[i];
        std::ostringstream linia;
        linia << (i + 1) << ". " << w.nick << " : "
              << w.trafione << " slow. w " << w.czas << "sec.";

        sf::Text tekst;
        tekst.setFont(czcionkaInterfejsu_);
        tekst.setCharacterSize(20);
        tekst.setFillColor(sf::Color::White);
        tekst.setString(linia.str());
        tekst.setPosition(450, 160 + i * 30);
        okno_.draw(tekst);
    }
}
    okno_.display();
}


