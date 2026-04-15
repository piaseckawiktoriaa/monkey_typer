#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Gra.h"
#include "Instrukcje.h"
#include <iostream>

std::string wprowadzNick(sf::RenderWindow& okno);

int main() {
    sf::RenderWindow okno(sf::VideoMode(800, 600), "Monkey Typer");
    Menu menu(okno);

    while (okno.isOpen()) {
        sf::Event e;
        while (okno.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                okno.close();
            menu.obsluzZdarzenia(e);
        }

        okno.clear();
        menu.rysuj();
        okno.display();

        if (menu.czyStartGry()) {
            std::string nick = wprowadzNick(okno);
            Gra gra(okno, nick);
            gra.uruchom();
            menu.resetuj();
        }

        else if (menu.czyPokazInstrukcje()) {
            Instrukcje instrukcje(okno, menu.getCzcionka());
            instrukcje.wyswietl();
            menu.resetuj();
        }
    }
    return 0;
}

std::string wprowadzNick(sf::RenderWindow& okno) {
    sf::Font font;
    font.loadFromFile("dane/czcionki/DejaVuSans.ttf");

    sf::Text tekst;
    tekst.setFont(font);
    tekst.setCharacterSize(30);
    tekst.setFillColor(sf::Color::White);
    tekst.setString("Podaj nick:");
    tekst.setPosition(100, 100);

    std::string nick;
    sf::Text nickTekst;
    nickTekst.setFont(font);
    nickTekst.setCharacterSize(30);
    nickTekst.setFillColor(sf::Color::Cyan);
    nickTekst.setPosition(100, 150);

    sf::Texture tloTekstura;
    if (!tloTekstura.loadFromFile("dane/tlogra.jpg")) {
        std::cerr << "Nie wczytano tla wprowadzania nicku!\n";
    }
    sf::Sprite tloSprite;
    tloSprite.setTexture(tloTekstura);
    float scaleX = static_cast<float>(okno.getSize().x) / tloSprite.getLocalBounds().width;
    float scaleY = static_cast<float>(okno.getSize().y) / tloSprite.getLocalBounds().height;
    tloSprite.setScale(scaleX, scaleY);

    bool zatwierdzony = false;

    while (okno.isOpen() && !zatwierdzony) {
        sf::Event e;
        while (okno.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                okno.close();

            if (e.type == sf::Event::TextEntered) {
                if (e.text.unicode == '\b' && !nick.empty()) {
                    nick.pop_back();
                } else if (e.text.unicode < 128 && std::isalnum(e.text.unicode)) {
                    if (nick.length() < 12)
                        nick += static_cast<char>(e.text.unicode);
                }
            }

            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter) {
                if (!nick.empty()) {
                    zatwierdzony = true;
                    break;
                }
            }
        }

        nickTekst.setString(nick);
        okno.clear();
        okno.draw(tloSprite);
        okno.draw(tekst);
        okno.draw(nickTekst);
        okno.display();
    }

    sf::Event dummy;
    while (okno.pollEvent(dummy)) {}

    return nick.empty() ? "Anonim" : nick;
}
