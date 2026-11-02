# CST209 C++ Group Assignment

A collaborative C++ project for the CST209 coursework.

## Team responsibilities

| Member | Responsibility |
|---|---|
| Member 1 | Part A |
| Member 2 | Part A |
| Member 3 | Parts B and C |
| Loh Haw Cherng | Part D |

## Repository structure

- `src/` — C++ source code
- `include/` — header files
- `docs/UML/` — UML diagrams
- `docs/Reports/` — reports and documentation
- `tests/` — test files

## Requirements

- C++17-compatible compiler (GCC / MinGW recommended)
- Git
- Visual Studio Code (recommended)

## Build and run

From the repository root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o group_assignment
```

Windows PowerShell:

```powershell
.\group_assignment.exe
```

Linux / macOS:

```bash
./group_assignment
```

## Team workflow

1. Pull the latest changes from `main` before starting work.
2. Work on a separate feature branch; do not commit directly to `main`.
3. Keep commits focused and use clear messages.
4. Push your branch and open a Pull Request into `main`.
5. Ask another member to review before merging.
6. Coordinate shared interfaces in `include/`.

### Suggested branches

- `feature/member1-partA`
- `feature/member2-partA`
- `feature/member3-partBC`
- `feature/member4-partD`

Store UML diagrams in `docs/UML/` and reports in `docs/Reports/`.
