# Analiza sortarilor

Proiectul compară experimental performanța a 6 algoritmi de sortare implementați în C și vizualizați ulterior cu Python:

- `BubbleSort`
- `InsertionSort`
- `SelectionSort`
- `ShellSort`
- `QuickSort`
- `MergeSort`

Benchmark-ul rulează pe mai multe dimensiuni de intrare, salvează timpii în `rezultate.csv`, iar `grafic.py` generează un grafic interactiv din aceste date.

## Structura proiectului

- `main.c` - implementează algoritmii, generează seturile de test și măsoară timpii de execuție
- `rezultate.csv` - rezultatele benchmark-ului în format tabelar
- `grafic.py` - citește CSV-ul și afișează grafice interactive cu Plotly
- `Analiza_sortarilor.pdf` - documentație/export asociat proiectului

## Ce testează programul

Pentru fiecare valoare `N`, programul generează 4 tipuri de date:

- `Random`
- `Sortat`
- `Inversat`
- `AproapeSortat`

Pentru fiecare set, rulează toți cei 6 algoritmi pe o copie a acelorași date și scrie în CSV:

- `N`
- `TipDate`
- `Algoritm`
- `TimpSec`

## Intervalul de testare

Programul pornește de la `N = 100` și ajunge până la `N = 1.000.000`, cu pași diferiți:

- `+100` până la `1000`
- `+1000` până la `10000`
- `+5000` până la `1000000`

Fișierul `rezultate.csv` existent conține:

- 217 valori distincte pentru `N`
- 4 tipuri de date
- 6 algoritmi

În total, rezultă `217 x 4 x 6 = 5208` măsurători.

## Observații importante despre implementare

- `QuickSort` folosește ultimul element ca pivot, deci poate intra în caz defavorabil pe date deja sortate sau inversate.
- `MergeSort` alocă memorie auxiliară la interclasare.
- Valorile din `Random` sunt generate cu `rand()`.
- La fiecare rulare, `rezultate.csv` este recreat de la zero.

## Exemple din rezultatele actuale

Pentru `N = 1.000.000`, în `rezultate.csv` apar, printre altele, următoarele valori:

| TipDate | Algoritm | TimpSec |
|---|---|---:|
| Random | QuickSort | 0.171411 |
| Random | MergeSort | 0.548118 |
| Sortat | InsertionSort | 0.003400 |
| Sortat | QuickSort | 1790.000000 |
| Inversat | ShellSort | 0.103644 |
| AproapeSortat | QuickSort | 0.197323 |

Aceste rezultate evidențiază bine diferența dintre algoritmii `O(n^2)` și cei mai eficienți pe intrări mari, dar și sensibilitatea implementării `QuickSort` la alegerea pivotului.

## Rulare

### 1. Compilare benchmark C

```bash
gcc -O2 -Wall -Wextra main.c -o analiza_sortari
```

### 2. Rulare benchmark

```bash
./analiza_sortari
```

La final se va genera sau suprascrie fișierul `rezultate.csv`.

### 3. Instalare dependențe pentru grafic

```bash
pip install pandas plotly
```

### 4. Afișare grafic interactiv

```bash
python3 grafic.py
```

Scriptul citește `rezultate.csv` și afișează un grafic de tip linie, separat pe coloane pentru fiecare `TipDate`.

## Cum este construit graficul

`grafic.py` folosește:

- `pandas` pentru citirea datelor
- `plotly.express` pentru vizualizare

Graficul:

- are axa `X` = `N`
- are axa `Y` = `TimpSec`
- colorează seriile după `Algoritm`
- separă vizual rezultatele cu `facet_col="TipDate"`
- folosește tema `plotly_dark`

## Limitări

- Timpul este măsurat cu `clock()`, deci depinde de platformă și de încărcarea sistemului.
- Benchmark-ul rulează algoritmi ineficienți și pentru `N` foarte mare, deci poate dura mult.
- `QuickSort` din implementarea curentă nu este optimizat pentru cazurile aproape sortate sau deja ordonate.

## Posibile îmbunătățiri

- înlocuirea pivotului fix din `QuickSort` cu median-of-three sau pivot aleator
- export automat al graficului în fișier
- repetarea fiecărui test de mai multe ori și calcularea unei medii
- adăugarea validării că vectorii sunt corect sortați după fiecare algoritm
