# zadanie_rek
Repozytorium zawiera program będący rozwiązaniem zadania 1, a także 2 plik pdf, jest to moja odpowiedź na zadania rekrutacyjne do podprojektu autonomy. 
### zad1.cpp
kod źrodłowy programu w języku C++ rozwiązujący zadanie 1.   
### opis_zadanie1.pdf 
dokładniejsze wyjaśnienie zastosowanych algorytmów, opisy funkcji, zasada działania i inne kluczowe kwestie w rozwiązaniu. 
### opis_zadanie2.pdf 
odpowiedź na podpunkt 2.1 oraz uwagi i pomysły związane z podpunktem 2.2 (którego niestety nie udało mi się sensownie rozwiązać w kodzie). 
                                                                 

# Wymagania
Do uruchomienia rozwiązania zad1 wymagany jest kompilator C++ z obsługą standardu C++11 lub nowszego (np. GCC 4.8+, Clang 3.3+, MSVC 2015+), a także system Windows/Linux/macOS.

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
3. **Kolejne n linii:** unikatowe id każdego pachołka, potem współrzędne x oraz y rozdzielone spacją.

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
Program wypisuje wynik działania na standardowe wyjście, w formacie:

## Nowe pachołki
Jeśli jakiekolwiek pachołki zostały scalone, wypisywane są informacje: 
1. **Pierwsza linia:** Komunikat tekstowy "New_ID, x, y, [Merged Cones]"
2. **Kolejne linie:** Dane kolejnych nowych pachołków w formacie: id, x, y [Merged Cones]. [Merged Cones] zawiera id scalonych pachołków oddzielone przecinkami.

## Otoczka
1. **Pierwsza linia:** Komunikat tekstowy: "Enclosure_Circumference, [Included Cones]"
2. **Druga linia:** obwód otoczki wypukłej oraz id pachołków, które ją tworzą. id pachołków są w nawiasie kwadratowym, oddzielone w środku przecinkami.


## Schemat wyjścia
```bash
New_ID, x, y, [Merged Cones]
id_1, x_1, y_1, [id_parent_1, id_parent_2 ...]
id_2, x_2, y_2, [id_parent_1, id_parent_2 ...]
...
Enclosure_Circumference, [Included Cones]
circumference, [id_1, id_2, id_3 ...]
```

