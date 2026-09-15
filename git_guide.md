# Team Git & GitHub Guide

Welcome to the firmware repository. Because this repository operates under a team-wide honor system for branch safety, **never commit or push code directly to `main`**. All work must be developed on a feature branch and merged via a Pull Request (PR).

---

## 1. Initial Local Setup (One-Time)

Before making your first commit, configure your name and email so your commits are properly attributed to your GitHub account:

```bash
git config --global user.name "Your Name"
git config --global user.email "your_github_email@example.com"
```

To clone this repository to your local machine:

```bash
git clone <repository_url>
cd <repository_folder>
```

---

## 2. Daily Development Workflow

Follow this 5-step lifecycle for every sensor, feature, or bug fix you work on.

### Step 1: Update Your Local `main`
Always pull the latest changes from GitHub before starting any new task to avoid merge conflicts:

```bash
git checkout main
git pull origin main
```

### Step 2: Create a Feature Branch
Create a descriptive branch dedicated strictly to the single task you are working on.

* **Format:** `feature/<topic>` or `fix/<topic>`
* **Examples:** `feature/imu-driver`, `feature/temp-sensor`, `fix/can-timing`

```bash
git checkout -b feature/<your-feature-name>
```

Verify you are on your new branch by checking:
```bash
git branch
```
*(An asterisk `*` will appear next to your active branch name.)*

### Step 3: Edit, Stage, and Commit

Work on your files locally. When you reach a logical stopping point, stage your changes:

* **Check which files changed:**
  ```bash
  git status
  ```

* **Inspect your changes line-by-line:**
  ```bash
  git diff
  ```

* **Stage specific files (never use `git add .` without checking status first):**
  ```bash
  git add common/include/<sensor_name>.hpp common/src/<sensor_name>.cpp
  ```

* **Commit with a clear, imperative message:**
  ```bash
  git commit -m "Scaffold interface and pseudocode for <sensor_name>"
  ```

### Step 4: Push to GitHub

Send your local branch up to the remote repository:

```bash
git push -u origin feature/<your-feature-name>
```
*(The `-u` flag links your local branch to the remote branch so future pushes just need `git push`.)*

### Step 5: Open a Pull Request (PR)

1. Open the repository on GitHub in your web browser.
2. A yellow banner will appear at the top: **"`feature/<your-feature-name>` had recent pushes"** &rarr; click **Compare & pull request**.
3. Fill out the PR form:
   * **Title:** Concise description of the work (e.g., `Add IMU driver interface and polling pseudocode`).
   * **Description:** Bullet out what files were created, what hardware interface is targeted, and any open questions.
4. On the right-hand panel, select at minimum Cole Schwab under **Reviewers**.
5. Click **Create pull request**.

---

## 3. Addressing PR Feedback & Merging

* If a reviewer requests changes:
  1. Open the files on your local machine and make the requested edits.
  2. Stage and commit the fixes:
     ```bash
     git add <changed_files>
     git commit -m "Address review comments: update scaling math"
     ```
  3. Push to your branch:
     ```bash
     git push
     ```
  4. The PR will automatically update with your new commits.
* Once approved, a team lead will click **Squash and merge** (or **Merge pull request**).
* Delete your feature branch on GitHub after merging to keep the repository clean.

---

## 4. Keeping Your Branch in Sync

If someone merges a PR into `main` while you are still working on your branch, bring your branch up to date:

```bash
# 1. Switch to main and get latest changes
git checkout main
git pull origin main

# 2. Switch back to your feature branch
git checkout feature/<your-feature-name>

# 3. Merge main into your branch
git merge main
```
* If there are no conflicts, Git will complete the merge automatically.
* Push the updated branch back to GitHub: `git push`.

---

## 5. What NOT to Do

* **Do not commit build artifacts:** Never commit `.hex`, `.bin`, `.elf`, `.o`, `.a`, `.exe`, or IDE folders (`.vscode/`, `.idea/`). Check `.gitignore` if these appear in `git status`.
* **Do not push directly to `main`:** Even though branch protection isn't enforced by GitHub, all code must go through a PR so the team stays aligned.
* **Do not use `git push --force` on shared branches:** Force-pushing overwrites history on GitHub and can destroy team members' work.
