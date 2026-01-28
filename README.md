# Implementacja PSO — projekt końcowy

Krótki, czytelny opis implementacji algorytmu Particle Swarm Optimization (PSO) w języku C.

## Opis

To repozytorium zawiera implementację PSO wraz z narzędziami pomocniczymi do obsługi mapy, logowania i konfiguracji. Kod jest napisany w C i przygotowany do skompilowania za pomocą dostarczonego `Makefile`.

## Wymagania

- Kompilator C (np. `gcc`)
- `make`

## Budowanie

W katalogu projektu uruchom:

```bash
make
```

To powinno wygenerować plik wykonywalny (`main` lub zgodnie z konfiguracją `Makefile`).

## Uruchamianie

Przykładowe uruchomienie programu:

```bash
./main
```

Program korzysta z pliku konfiguracyjnego `pso_config.txt` (w katalogu głównym). Edytuj go przed uruchomieniem, aby zmienić parametry algorytmu (np. liczba cząstek, liczba iteracji, współczynniki PSO).

## Pliki w repozytorium

- `main.c` — punkt wejścia programu.
- `pso.c`, `pso.h` — implementacja algorytmu PSO.
- `pso_config.txt` — przykładowa konfiguracja parametrów PSO.
- `obsluga_map.c`, `obsluga_map.h` — obsługa mapy/struktur danych wejściowych.
- `narzedzia_pomocnicze.c`, `narzedzia_pomocnicze.h` — funkcje pomocnicze.
- `logger.c`, `logger.h` — prosty logger zapisujący dane do `log.csv`.
- `log.csv` — (wynikowy) plik z logami/rezultatami (jeśli wygenerowany).
- `test_map.txt` — przykładowa mapa/test wejściowy.

## Konfiguracja (`pso_config.txt`)

Plik konfiguracyjny zawiera parametry sterujące zachowaniem PSO. Typowe parametry, które możesz zobaczyć i zmienić:

- `num_particles` — liczba cząstek
- `iterations` — liczba iteracji
- `w` — współczynnik bezwładności
- `c1`, `c2` — współczynniki przyciągania do najlepszej pozycji

Uwaga: dokładne nazwy i format parametrów zależą od implementacji w `pso.c` — sprawdź plik, by dopasować wartości.

## Wyniki i logowanie

Domyślnie program zapisuje dane do `log.csv`. Możesz analizować ten plik lub użyć własnych narzędzi do wizualizacji wyników optymalizacji.

## Testy

Do szybkiego testu użyj `test_map.txt` jako wejścia (jeżeli program obsługuje mapy z tego pliku). Uruchom program i sprawdź `log.csv` oraz wyjście w konsoli.

## Wkład i modyfikacje

- Chcesz dodać nowe funkcje? Otwórz pull request lub skontaktuj się z autorem projektu.
- Jeśli chcesz, mogę dodać przykładowy skrypt do wizualizacji wyników lub zautomatyzowane testy.

## Licencja

Brak pliku licencyjnego w repozytorium. Jeśli chcesz opublikować projekt, dodaj proszę plik `LICENSE` z odpowiednią licencją (np. MIT).

---

Autor: projekt studencki — edytuj i dostosuj opis oraz parametry konfiguracyjne do własnych potrzeb.
