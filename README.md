# 🐵 Monkey Typer
![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![SFML](https://img.shields.io/badge/SFML-graphics-green)

Gra typu *typing game* napisana w języku C++ z wykorzystaniem biblioteki SFML.  
Celem gracza jest jak najszybsze wpisywanie pojawiających się na ekranie słów.

---

## 🎮 Gameplay

Gracz wpisuje słowa wyświetlane na ekranie, zanim znikną.  
Za każde poprawne słowo otrzymuje punkty, a pominięcie powoduje utratę życia.  
Gra stopniowo przyspiesza, zwiększając poziom trudności.

---

## 📸 Gameplay

<p align="center">
  <img src="https://github.com/user-attachments/assets/3a952258-e4c2-42fc-8410-70cc88bf527b" width="300"/>
  <img src="https://github.com/user-attachments/assets/3d8013da-9ea1-4045-bfaa-c4da8359e281" width="300"/>
  <img src="https://github.com/user-attachments/assets/e6e677b8-06f1-496c-8e50-06c1b4729937" width="300"/>
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/e25af14c-96af-4492-b46f-d87438762836" width="300"/>
  <img src="https://github.com/user-attachments/assets/b7e2ce5e-6fc9-42aa-bafe-b7dcffcf2070" width="300"/>
  <img src="https://github.com/user-attachments/assets/47283cb1-f87f-4e47-b86b-1cea9f063d89" width="300" />
</p>
---

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

---

## 🛠️ Technologie

- C++
- SFML (grafika, dźwięk, obsługa okna)
- programowanie obiektowe (OOP)
- operacje na plikach (config, ranking)

---

## 🏆 Wyniki

Po zakończeniu rozgrywki wyświetlane jest podsumowanie zawierające:
- nick gracza
- liczbę poprawnie wpisanych słów
- czas gry

Wyniki są zapisywane do pliku: wyniki.txt

---

## ▶️ Uruchomienie

### Wymagania

* C++
* SFML
* CMake

### Kroki

```bash
cmake -S . -B build
cmake --build build
./build/monkey_typer
```

Po zbudowaniu projektu aplikację można uruchamiać ponownie bez kompilacji:

```bash
cd build
./monkey_typer
```
