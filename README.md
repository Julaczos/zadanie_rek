# zadanie_rek
Program to rozwiązanie do zadania 1 do podprojektu Autonomy, najpierw scala pachołki, a następnie oblicza obwód otoczki. W pliku "opis_zadanie1.pdf" znajduje się dokładniejsze wyjaśnienie zastosowanych algorytmów, opisy funkcji main oraz pozostałych i inne kluczowe kwestie.                                                                        

# Wymagania
Do uruchomienia wymagany jest kompilator C++ z obsługą standardu C++11 lub nowszego (np. GCC 4.8+, Clang 3.3+, MSVC 2015+), a także system Windows/Linux/macOS.

## Poradnik uruchomienia
### 1. Klonowanie repozytorium
```bash
git clone https://github.com/Julaczos/zadanie_rek
cd zadanie_rek
```

### 2. Kompilacja
#### Linux & macOS
```bash
g++ zad1.cpp -o program
./program
```

#### Windows
```bash
g++ zad1.cpp -o program.exe
.\program.exe
```
# Dane wejściowe
Program przyjmuje dane na standardowym wejściu (`stdin` / konsola) w następującym formacie:

1. **Pierwsza linia:** Liczba całkowita n określająca liczbę pachołków.
2. **Druga linia:** Liczba zmiennoprzecinkowa m określająca minimalną odległość między pachołkami
3. **Kolejne $ linii:** unikatowe id każdego pachołka, potem współrzędne x oraz y rozdzielone spacją.

### Schemat:
```text
n
m
id_1 x_1 y_1
id_2 x_2 y_2
...
id_n x_n y_n
```

# Wynik programu
Program wypisuje wynik działania na standardowe wyjście (konsola), w formacie:

## Nowe pachołki
Jeśli jakiekolwiek pachołki zostały scalone, wypisywane są informacje: 
1.**Pierwsza linia:** Komunikat tekstowy "New_ID, x, y, [Merged Cones]"
2.**Kolejne linie:** Dane kolejnych nowych pachołków w formacie: id, x, y [Merged Cones]. [Merged Cones] zawiera id scalonych pachołków oddzielone przecinkami.

## Otoczka
1. **Pierwsza linia:** Komunikat tekstowy: "Enclosure_Circumference, [Included Cones]"
2. **Druga linia:** obwód otoczki wypukłej oraz id pachołków, które ją tworzą. ID są w nawiasie kwadratowym, oddzielone w środku przecinkami.


## Schemat wyjścia
```bash
New_ID, x, y, [Merged Cones]
id_1, x_1, y_1, [id_a, id_b ...]
id_2, x_2, y_2, [id_z, id_w ...]
...
Enclosure_Circumference, [Included Cones]
circumference, [id_1, id_2, id_3 ...]
```

