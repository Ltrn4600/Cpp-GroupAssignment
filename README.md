# CST209 C++ Group Assignment

A collaborative C++ project for the CST209 coursework.

## Team responsibilities

| Member | Responsibility | Upload location |
|---|---|---|
| Member 1 | Write the Part A report | `docs/Reports/Member1/` |
| Member 2 | Write the Part A report | `docs/Reports/Member2/` |
| Member 3 | Create UML diagrams for Parts B and C | `docs/UML/PartB/` and `docs/UML/PartC/` |
| Member 4 | Develop the C++ code | `src/` and `include/` |

## Repository structure

- `src/` — C++ source files (`.cpp`)
- `include/` — C++ header files (`.h` / `.hpp`)
- `docs/Reports/Member1/` — Member 1's report
- `docs/Reports/Member2/` — Member 2's report
- `docs/UML/PartB/` — UML diagrams for Part B
- `docs/UML/PartC/` — UML diagrams for Part C
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

1. Pull the latest changes from `main` before starting.
2. Work on your assigned branch; do not commit directly to `main`.
3. Keep commits focused and use clear messages.
4. Push your branch and open a Pull Request into `main`.
5. Ask another member to review before merging.
6. Coordinate code interfaces and file names with Member 4 before changing shared code.

## Suggested branches

- `docs/member1-report`
- `docs/member2-report`
- `docs/member3-uml`
- `feature/member4-code`

Use descriptive file names, for example `Member1_PartA_Report.pdf`, `PartB_ClassDiagram.png`, or `MainMenu.cpp`.
