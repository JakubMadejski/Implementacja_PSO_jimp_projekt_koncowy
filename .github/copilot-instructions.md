# Repo-specific Copilot instructions

This repository implements a Particle Swarm Optimization (PSO) in C. Use these notes to be immediately productive when authoring or modifying code.

- **Big picture:** CLI program that reads a map (grid of doubles), runs PSO on that map, and logs particle states to a CSV. The main flow is in `main.c` which: parses flags, loads a map, initializes the logger, initializes the swarm (`pso`), runs iterations, and writes to `log.csv`.

- **Key files:** `Makefile`, `main.c`, `pso.c`, `pso.h`, `obsluga_map.c`, `obsluga_map.h`, `logger.c`, `pso_config.txt`, `test_map.txt`.

- **Build / run:**
  - Build: run `make` (target builds `pso` from all `.c` files).
  - Run example: `./pso test_map.txt -p 50 -i 200 -c pso_config.txt -n 10`.
  - The `Makefile` sets `CC = cc`, `CFLAGS = -std=c11 -Wall -Wextra -I.`, and links math with `-lm`.

- **Command-line behavior / flags (observed in `main.c`):**
  - positional: `<plik_mapy>` (first arg)
  - `-p <n>`: number of particles (default 30)
  - `-i <n>`: iterations (default 100)
  - `-c <file>`: optional PSO config file (three doubles: `w c1 c2`)
  - `-n <k>`: save state every `k` iterations (default 1)

- **Map format (important):** `obsluga_map.c` expects the first two numbers to be width and height (ints), followed by `width*height` doubles representing grid values. Use `test_map.txt` as example.

- **PSO specifics (pso.c / pso.h):**
  - Main types: `Czasteczka` and `Roj`.
  - API to read/modify: `inicjalizuj_roj`, `aktualizuj_roj`.
  - Particles store position `x,y`, velocity `vx,vy`, local best `(najlepsze_x,y)` and `najlepsza_wartosc`; global best stored in `Roj`.
  - Boundaries: positions are clamped to map edges, velocity reflected and damped by 0.5.

- **Config file (`pso_config.txt`):** Accepts three floats separated by whitespace: `w c1 c2`. If file missing or malformed, defaults are used (`w=0.5`, `c1=1.0`, `c2=1.0`). Example present in repository.

- **Logging / output:** `logger.c` writes CSV rows with header `Iteracja,ID_Czastki,X,Y,Wartosc,pBestVal`. The program writes to `log.csv` by default and the `Makefile` `clean` target removes it.

- **Code patterns & conventions to follow when changing code:**
  - Minimal error handling: functions typically print to `stderr` or call `perror()` and return `NULL` or exit; follow the same pattern when adding error paths.
  - Manual memory management: `malloc`/`free` are used throughout — ensure symmetric frees (e.g., `usun_mape`).
  - Use `double` for numeric values and `int` for sizes/indices; map indexing is `dane[y * szerokosc + x]`.
  - Naming is Polish; maintain existing identifiers (e.g., `inicjalizuj_roj`, `pobierz_wartosc`) to keep consistency with the codebase.

- **Where to look when debugging:**
  - Argument parsing and defaults: `main.c`.
  - Map parsing errors: `obsluga_map.c` — confirm width/height read and `dane` allocation.
  - PSO behavior: `pso.c` — velocity update, clamping, and global/local best updates.
  - CSV output correctness: `logger.c` (header format and numeric formatting).

- **Quick examples to include in code changes / PRs:**
  - Small patch that adds a `--help` flag printing usage in `main.c`.
  - Unit test harness (not present) could be a small C program that calls `wczytaj_mape` and `pobierz_wartosc` on `test_map.txt` and asserts expected values.

- **What not to change casually:**
  - Public APIs in `pso.h` and `obsluga_map.h` (other modules rely on them).
  - CSV header format (external tools may parse `log.csv`).

If anything above is unclear or you want instructions in English, tell me which section to expand or revise.
