# Cpp-GroupAssignment — Git Collaboration Rules

This repository is a student-owned C++ group assignment. **Students are responsible for the coursework itself. AI is only a Git/repository maintenance assistant.**

## 1. Responsibility boundary (AI / 学生职责)

| Task | Students | AI assistant |
|---|---|---|
| Coursework requirements, design and feature implementation | Own and perform | Not responsible; do not implement |
| Writing or rewriting C++ assignment logic | Own and perform | Do not perform |
| Checking branch status, diffs, history and pull requests | May perform | Allowed |
| Diagnosing Git errors, merge conflicts, and build/test error logs | Decide fixes | Allowed to inspect and explain; no autonomous coursework code changes |
| Creating branches and commits | Approve/request | Allowed on request |
| Reviewing and merging pull requests | Approve changes | Allowed to inspect; merge only after explicit student approval |
| Force push, delete branches, destructive history rewrite | Explicit team decision required | Never do automatically |

**AI rules:**
1. Do not independently develop, complete, or refactor coursework functionality.
2. Do not change C++ source code to resolve errors unless the team explicitly requests a specific change and the coursework policy permits it. Normally, report errors for students to fix.
3. Before a commit, check the branch and changed files. Commit only intended changes and report the resulting commit SHA.
4. Before a merge, check the source/target branches, diff, conflicts, and available test results. Never interpret an absence of tests as a pass.
5. Merge only after an explicit team instruction identifying what should be merged. Do not approve your own changes on behalf of students.
6. Do not use force push, branch deletion, or history rewriting without a separate explicit request and risk review.
7. If repository rules conflict with a request, describe the conflict instead of silently changing the rules.

中文简述：**AI 只负责 Git 仓库检查、报错分析、分支、提交、PR 审查与经授权的合并；不自主编写作业、不替学生决定功能，也不得擅自修改或覆盖他人代码。**

## 2. Branch and main workflow

- `main`: stable team-reviewed integration and submission baseline.
- `feature/<member-or-task>`: student-owned work branches created from the latest `main`.
- `docs/<topic>` or `chore/<topic>`: documentation or maintenance changes.
- A separate `dev` branch is **not required** for this four-member workflow.

Workflow:

```text
main
  ├── feature/member1-partA ── PR ──> main
  ├── feature/member2-partA ── PR ──> main
  ├── feature/member3-partBC ── PR ──> main
  ├── feature/member4-partD  ── PR ──> main
  └── docs/ai-git-workflow   ── PR ──> main
```

A branch is isolated until merged. **Never commit normal development directly to `main`.** Open a PR, review the diff, request another team member's approval, resolve conflicts, and then merge. Protect `main` with required PR reviews if repository administration access is available; written rules alone do not enforce this.

## 3. Basic Git commands

Start work:

```bash
git clone https://github.com/Ltrn4600/Cpp-GroupAssignment.git
cd Cpp-GroupAssignment
git switch main
git pull --ff-only origin main
git switch -c feature/your-task
```

Commit your own changes:

```bash
git status
git diff
git add <specific-files>
git commit -m "Describe your change"
git push -u origin feature/your-task
```

Open a pull request with **base: `main`** and **compare: your branch**. Confirm another team member has approved before asking AI to merge.

Update an existing feature branch safely:

```bash
git fetch origin
git switch feature/your-task
git merge origin/main
```

For conflicts: inspect them, let the affected student decide behavioral changes, then commit the resolution. Avoid forcing an automatic resolution of conflicting coursework code.

## 4. AI operation checklist

When asked to maintain the repository, the AI should report:
- Target repository and source/target branch
- What it inspected (diff, commit range, conflicts, tests if available)
- Exactly what changed or was merged
- Commit SHA / PR reference where applicable
- Errors, unverified assumptions, and remaining risks

**Scope:** this document only defines collaboration and AI repository permissions. It does not specify the assignment features, code architecture, or grading requirements.
