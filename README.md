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
- zapis wyników do pliku (ranking)
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
Wyniki zapisywane są w pliku: wyniki.txt

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

*Po zbudowaniu projektu aplikację można uruchamiać również ponownie bez kompilacji:
cd build
./monkey_typer 

## 📸 Gameplay
<img width="800" height="631" alt="image" src="https://github.com/user-attachments/assets/3a952258-e4c2-42fc-8410-70cc88bf527b" />
<img width="796" height="629" alt="image" src="https://github.com/user-attachments/assets/3d8013da-9ea1-4045-bfaa-c4da8359e281" />
<img width="794" height="622" alt="image" src="https://github.com/user-attachments/assets/e6e677b8-06f1-496c-8e50-06c1b4729937" />
<img width="782" height="623" alt="image" src="https://github.com/user-attachments/assets/e25af14c-96af-4492-b46f-d87438762836" />
<img width="794" height="628" alt="image" src="https://github.com/user-attachments/assets/bea47367-fd41-49f6-bb34-fa1582ce5a0b" />
<img width="792" height="617" alt="image" src="https://github.com/user-attachments/assets/77a184ea-ebf3-4024-8bbc-7682a366a3ec" />
<img width="799" height="622" alt="image" src="https://github.com/user-attachments/assets/51c98bcc-3959-4957-837a-31211e1ee96a" />


## 💡 Informacje
Projekt został wykonany w ramach zajęć na studiach i prezentuje:
- programowanie zdarzeniowe
- implementację pętli gry
- tworzenie prostych gier 2D w C++
