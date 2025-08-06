# 🤝 Contributing to `whattheshell`

Welcome! We're excited that you're interested in contributing to **`whattheshell`**, a creative shell-based project made by and for hackers, learners, and tinkerers. 🚀

This guide helps you contribute **cleanly and repeatedly**, whether you're fixing typos or building features.

---

## 🛠️ One-Time Setup

1. **Fork this repo**
   - Go to [https://github.com/apaleblueman/whattheshell](https://github.com/apaleblueman/whattheshell)
   - Click **Fork** (top-right)

2. **Clone your fork**
   ```bash
   git clone https://github.com/YOUR_USERNAME/whattheshell.git
   cd whattheshell
   ```

3. **Add the original repo as upstream**
   ```bash
   git remote add upstream https://github.com/apaleblueman/whattheshell.git
   git remote -v  # should show both origin and upstream
   ```

---

## 🔁 The Contribution Cycle (Follow Every Time You Add Something)

### 1️⃣ Sync your fork before starting
```bash
git checkout main
git pull --rebase upstream main
git push origin main
```

### 2️⃣ Create a new feature/fix branch
```bash
git checkout -b feature/your-task-name
```
Examples:
- `feature/add-prompt-emoji`
- `fix/parse-error`

**📌 Always use a separate branch for each PR. Don’t work on `main`.**

### 3️⃣ Do your work
- Edit, commit regularly.
- Keep changes focused.
```bash
git add .
git commit -m "Add emoji to prompt"
```

### 4️⃣ Push to your fork
```bash
git push origin feature/your-task-name
```

### 5️⃣ Open a Pull Request
- Go to your fork on GitHub.
- Click **Compare & pull request**.
- Set:
  - **base repo:** `apaleblueman/whattheshell`
  - **base branch:** `main`
  - **head repo:** your fork
  - **head branch:** your feature branch
- Add a clear title + description

### 6️⃣ Wait for review and feedback
Maintainer will:
- Review the PR 🕵️‍♂️
- Request changes (if needed)
- Merge into `main` ✅

### 7️⃣ Clean up after merge
```bash
git checkout main
git pull --rebase upstream main
git push origin main

# Optional: Delete branch
git branch -d feature/your-task-name
git push origin --delete feature/your-task-name
```

---

## 💡 Pro Tips

- Pull with `--rebase` to avoid messy merge commits:
  ```bash
  git pull --rebase upstream main
  ```
- Write clear commit messages
- Don’t mix unrelated changes in one PR
- Ask in Discord `#help` if you're stuck!

---

## 🧪 Sample Script (optional)
`sync.sh` — use this before any new task:
```bash
#!/bin/bash
git checkout main
git fetch upstream
git pull --rebase upstream main
git push origin main
```
Run it like this:
```bash
bash sync.sh
```

---

### 🔀 Resolving Merge Conflicts

Sometimes, if two contributors edit the same part of a file (e.g., `README.md`), Git can't merge changes automatically and shows a **merge conflict**.

#### 📌 When does this happen?

If your Pull Request (PR) is behind the main branch and someone else's PR was merged first, you'll need to resolve the conflict **before your PR can be merged**.

---

#### 🛠️ How to Fix It (Using Terminal + Any Editor)

1. **Make sure you're on your feature branch:**

   ```bash
   git checkout <your-feature-branch>
   ```

2. **Pull the latest changes from `main`:**

   ```bash
   git fetch origin
   git pull origin main
   ```

   > ⚠️ If there's a conflict, Git will tell you which file(s) need to be fixed.

3. **Open the conflicted file** in your editor (e.g., VS Code) and look for markers:

   ```c
   <<<<<<< HEAD
   Your changes
   =======
   Changes from main branch
   >>>>>>> main
   ```

4. **Manually edit the file** to keep what you need, then **remove the conflict markers**.

5. **Add and commit the resolved file:**

   ```bash
   git add <file>
   git commit -m "Resolved merge conflict"
   ```

6. **Push your updated branch:**

   ```bash
   git push origin <your-feature-branch>
   ```

7. ✅ Your PR on GitHub will now show “This branch has no conflicts” — you're good to go!

---


## 🙌 Thanks for contributing!
Together, we’re making `whattheshell` better, cooler, and geekier.

---

Feel free to ping the maintainer `@apaleblueman` or ask in our Discord!

> _Hack the shell, change the world._
