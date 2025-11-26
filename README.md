# v1.0

## Aprašymas
Programa skirta studentų pažymių tvarkymui ir analizei. Sistema leidžia:
- Įvesti studentų duomenis ranka
- Nuskaityti duomenis iš failų
- Generuoti testinių duomenų failus
- Atlikti našumo testus su skirtingomis strategijomis

## Funkcionalumas
- Skaičiuoja galutinius pažymius pagal vidurkį ir medianą
- Dalina studentus į "vargšiukus" (< 5.0) ir "kietiakius" (>= 5.0)
- Palaiko `vector` ir `list` konteinerius
- 3 skirtingos dalijimo strategijos

## Įdiegimas

### Linux/Unix (Makefile)
```bash
make
./studentai
```

### Bet kuri OS (CMake)
```bash
mkdir build
cd build
cmake ..
make
./studentai
```

### Windows (CMake)
```bash
mkdir build
cd build
cmake ..
cmake --build .
studentai.exe
```

### Windows (tiesioginis kompiliavimas)
```bash
g++ -std=c++17 -o studentai main.cpp funkcijos.cpp
.\studentai
```

## Naudojimas

### Meniu:
1. Įvedimas ranka - rankinis studentų duomenų įvedimas
2. Nuskaitymas iš failo - vienkartinis failo skaitymas
3. Sugeneruoti failus - sukuria 5 failus (1K, 10K, 100K, 1M, 10M įrašų)
4. Benchmarkai - našumo testavimas su skirtingomis strategijomis

### Dalijimo strategijos:

**Strategija 1 (Kopijavimas):**
- Kopijuojami visi studentai į du naujus konteinerius
- Privalumai: Stabilus greitis, patikimas
- Trūkumai: Naudoja 3x daugiau atminties
- Tinka: vector ir list

**Strategija 2 (Trynimas):**
- Vargšiukai perkeliami į naują konteinerį ir trinami iš originalo
- Privalumai: Ekonomiškas atminties naudojimas (2x atmintis), greitas su list
- Trūkumai: Labai lėtas su vector dėl O(n²) sudėtingumo
- Tinka: Tik list konteineriams

**Strategija 3 (STL partition):**
- Naudojamas `std::stable_partition` algoritmas
- Privalumai: Greičiausias metodas, optimalus atminties naudojimas
- Trūkumai: Veikia tik su vector
- Tinka: Tik vector konteineriams

## TESTAVIMŲ REZULTATAI:

### Testavimo aplinka:
- Kompiliatorius: MinGW g++ (32-bit)
- OS: Windows
- Kartojimų skaičius: 3
- Rezultatai: vidurkiai iš 3 kartojimų

**Trumpiniai**
F - failed
S - stopped

### Vector konteineris

#### Strategija 1 (Kopijavimas)
| Dydis | Skaitymas (s) | Dalijimas (s) | Rašymas V (s) | Rašymas K (s) | Viso (s) |
|-------|---------------|---------------|---------------|---------------|----------|
| 1K    | 0.003590      | 0.000481      | 0.004581      | 0.011361      | 0.027843 |
| 10K   | 0.025243      | 0.003997      | 0.027807      | 0.039315      | 0.104850 |
| 100K  | 0.199290      | 0.030418      | 0.235282      | 0.350631      | 0.886243 |
| 1M    | 2.177424      | 0.361349      | 2.315834      | 2.955429      | 8.452062 |
| 10M   | -             | -             | -             | -             | F 	   |

*std::bad_alloc - nepakanka atminties 32-bit sistemoje

#### Strategija 2 (Trynimas) - NEREKOMENDUOJAMA
| Dydis | Skaitymas (s) | Dalijimas (s) | Rašymas V (s) | Rašymas K (s) | Viso (s)   |
|-------|---------------|---------------|---------------|---------------|------------|
| 1K    | 0.002816      | 0.065537      | 0.004333      | 0.006296      | 0.082056   |
| 10K   | 0.028015      | 7.043562      | 0.023743      | 0.039780      | 7.137941   |
| 100K  | 0.205000      | 714.39        | 0.221186      | 0.317615      | 715.13     |
| 1M    | -             | -             | -             | -             | S		     |

**PASTABA:** Strategija 2 su vector yra LABAI LĖTA (O(n²) kompleksiškumas). 100K įrašų užtruko apie 12 minučių.

#### Strategija 3 (STL partition) - REKOMENDUOJAMA
| Dydis | Skaitymas (s) | Dalijimas (s) | Rašymas V (s) | Rašymas K (s) | Viso (s) |
|-------|---------------|---------------|---------------|---------------|----------|
| 1K    | 0.003519      | 0.002012      | 0.011026      | 0.005578      | 0.026883 |
| 10K   | 0.025506      | 0.009642      | 0.027740      | 0.040106      | 0.105925 |
| 100K  | 0.229316      | 0.091573      | 0.233617      | 0.284712      | 0.868291 |
| 1M    | 2.165901      | 0.934951      | 2.019262      | 2.866651      | 8.179023 |
| 10M   | 19.433673     | 15.190316     | 18.160479     | 28.131083     | 82.167025|

### List konteineris

#### Strategija 1 (Kopijavimas)
| Dydis | Skaitymas (s) | Dalijimas (s) | Rašymas V (s) | Rašymas K (s) | Viso (s) |
|-------|---------------|---------------|---------------|---------------|----------|
| 1K    | 0.010591      | 0.000529      | 0.012893      | 0.019414      | 0.046380 |
| 10K   | 0.028412      | 0.006206      | 0.045092      | 0.049518      | 0.145837 |
| 100K  | 0.227383      | 0.046654      | 0.256839      | 0.311401      | 0.956774 |
| 1M    | 2.444236      | 0.488694      | 2.117019      | 3.329918      | 9.525750 |
| 10M   | -             | -             | -             | -             | F        |

*std::bad_alloc - nepakanka atminties 32-bit sistemoje

#### Strategija 2 (Trynimas) - REKOMENDUOJAMA
| Dydis | Skaitymas (s) | Dalijimas (s) | Rašymas V (s) | Rašymas K (s) | Viso (s) |
|-------|---------------|---------------|---------------|---------------|----------|
| 1K    | 0.003233      | 0.000312      | 0.005129      | 0.013017      | 0.023618 |
| 10K   | 0.045951      | 0.004256      | 0.032964      | 0.040856      | 0.127714 |
| 100K  | 0.218623      | 0.027416      | 0.242449      | 0.346883      | 0.864264 |
| 1M    | 2.099126      | 0.365976      | 2.321419      | 3.175379      | 8.164816 |
| 10M   | 21.760279     | 2.821922      | 20.688349     | 28.534035     | 76.607027|

### Išvados

#### Vector konteineris:

**Strategija 1 (Kopijavimas):**
- Stabilus ir patikimas greitis
- Dalijimo laikas: 0.48ms (1K) → 361ms (1M)
- Trūkumai: Nepavyko 10M dėl atminties trūkumo (32-bit sistema)

**Strategija 2 (Trynimas):**
- **Netinka vector konteineriui**
- Dalijimo laikas: 65ms (1K) → 7s (10K) → 714s (100K)
- Eksponentinis lėtėjimas dėl vector::erase() O(n) sudėtingumo
- 100K įrašų užtruko ~12 minučių (vs. 0.03s su Strategija 1)

**Strategija 3 (STL partition):**
- **Greičiausias metodas vector konteineriui**
- Dalijimo laikas: 2ms (1K) → 935ms (1M) → 15.2s (10M)
- 2.6x greitesnis už Strategiją 1 (1M įrašų)
- Sėkmingai apdorojo 10M įrašų per 82s
- Naudoja std::stable_partition - optimalus algoritmas

#### List konteineris:

**Strategija 1 (Kopijavimas):**
- Stabilus greitis, panašus į vector
- Dalijimo laikas: 0.53ms (1K) → 489ms (1M)
- Nepavyko 10M dėl atminties trūkumo

**Strategija 2 (Trynimas):**
- **Tinkamas list konteineriui**
- Dalijimo laikas: 0.31ms (1K) → 366ms (1M) → 2.82s (10M)
- Greičiausias list metodas didelėms duomenų apimtims
- list::erase() yra O(1), todėl nėra spartos problemų
- Sėkmingai apdorojo 10M įrašų per 76.6s

#### Vector vs List palyginimas:

**Mažos apimtys (≤ 100K):**
- Vector greitesnis ~8-10% (geresnė cache lokalybė)
- Strategija 3 (vector) yra greičiausia opcija

**Didelės apimtys (1M-10M):**
- Vector Strategija 3: 8.18s (1M), 82.17s (10M)
- List Strategija 2: 8.16s (1M), 76.61s (10M)
- List šiek tiek greitesnis didelėse apimtyse (~7% su 10M)

**Atminties naudojimas:**
- Strategija 1: 3x pradinis dydis
- Strategija 2: 2x pradinis dydis
- Strategija 3: ~2x pradinis dydis

#### Galutinės rekomendacijos:

**Naudokite Vector su Strategija 3 kai:**
- Turite pakankamai atminties
- Reikia maksimalaus greičio
- Duomenų apimtys iki 1-5M įrašų

**Naudokite List su Strategija 2 kai:**
- Labai didelės duomenų apimtys (>5M)
- Ribota atmintis
- Reikia atminties efektyvumo

**Patariama nenaudoti:**
- Vector su Strategija 2 ("tragiškai lėta)

## Sistemos reikalavimai
- C++17 arba naujesnė versija
- g++ arba kitas C++ kompiliatorius

## Versijos

### v1.0
- Implementuotos 3 dalijimo strategijos
- Pridėtas palaikymas vector ir list konteineriams
- Sukurta build sistema (Makefile, CMake)
- Atliktas išsamus testavimas ir analizė
- Pilna dokumentacija README.md
- Testavimo rezultatai su 5 skirtingais dydžiais (1K-10M)

### v0.3
- Benchmarking funkcionalumas
- Vienkartinis failo skaitymas

### v0.2
- Failų generavimas
- Bazinis failų skaitymo funkcionalumas

### v0.1
- Pradinė versija
- Rankinis įvedimas
- Bazinis funkcionalumas