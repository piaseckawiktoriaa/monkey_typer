# 🐵 Monkey Typer

Gra typu „typing game” napisana w języku C++ z wykorzystaniem biblioteki SFML, w której gracz musi jak najszybciej wpisywać spadające słowa.

## 🎮 Rozgrywka
Na ekranie pojawiają się słowa, które gracz musi wpisać z klawiatury.  
Poprawne wpisanie słowa zwiększa wynik, natomiast pominięcie powoduje utratę życia.  
Gra stopniowo zwiększa poziom trudności.

## ✨ Funkcjonalności
- rozgrywka w czasie rzeczywistym
- dynamiczne generowanie słów
- system punktów i żyć
- skalowanie trudności
- pauza w trakcie gry
- zapis wyników do pliku
- ranking wyświetlany po zakończeniu rozgrywki
- konfiguracja gry z pliku
- obsługa dźwięków i grafiki

## 🛠️ Technologie
- C++
- SFML (grafika, dźwięk, obsługa okna)
- programowanie obiektowe (OOP)
- operacje na plikach (config, ranking)

## 📁 Struktura projektu
- `main.cpp` – punkt wejścia programu  
- `Gra` – logika gry  
- `Menu` – menu główne  
- `Instrukcje` – ekran instrukcji  
- `Konfiguracje` – wczytywanie ustawień  
- `Slowo` – obsługa słów i logiki wpisywania  
- `dane/` – zasoby (czcionki, dźwięki, obrazy, config, lista słów)

## ⚙️ Konfiguracja
Gra korzysta z pliku `config.txt`, w którym można zmienić m.in.:
- rozmiar okna
- liczbę żyć
- czas gry
- rozmiary czcionek

## 🏆 Ranking
Po zakończeniu rozgrywki wyświetlane jest podsumowanie zawierające:
- nick gracza
- liczbę poprawnie wpisanych słów
- czas gry

Wyniki są zapisywane do pliku:
`dane/wyniki.txt`

Dodatkowo po zakończeniu gry wyświetlany jest ranking najlepszych wyników.

## ▶️ Uruchomienie

### Wymagania
- C++
- SFML
- CMake

### Kroki

```bash
cmake -S . -B build
cmake --build build
./build/monkey_typer
