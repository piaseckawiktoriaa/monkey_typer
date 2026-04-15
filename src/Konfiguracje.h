#pragma once
#include <string>

struct Konfiguracje {
    float predkoscStartowa;
    float interwalSpawnu;
    int limitCzasu;
    std::string sciezkaCzcionki;

    void wczytajZPliku(const std::string& nazwaPliku);
};
