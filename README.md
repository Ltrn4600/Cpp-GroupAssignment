# CST209 C++ Group Assignment

A small C++ group coursework repository. Students write and review the assignment; AI only assists with Git maintenance.

## Files

- `src/main.cpp` — current program entry point
- `.gitignore` — ignore generated files

Add source files, headers, UML diagrams and reports **when they are actually needed**. Do not create empty folders in advance.


Each member works on their own `feature/*` branch and opens a Pull Request to `main`. Another member reviews before merging. `main` is the shared stable version; no separate `dev` branch is necessary.

## AI responsibility boundary

AI may **inspect Git status/diffs, diagnose errors or conflicts, create branches and commits on request, review PRs, and merge only with explicit team approval**.

AI must **not** independently implement or rewrite coursework features, change project requirements, overwrite another member's work, force-push, or delete active branches without explicit approval. Compilation errors may be explained, but coursework code corrections remain the students' responsibility.

## Build (current starter program)

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o group_assignment
```

Run `./group_assignment` on Linux/macOS or `.\group_assignment.exe` on Windows. Update this command when more source files are added.
