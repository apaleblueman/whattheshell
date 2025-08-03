````md
# 🙌 Contributing to WhatTheShell

Thank you for considering contributing to **WhatTheShell**! This guide will walk you through everything you need to know to contribute effectively.

---

## 🧰 Prerequisites

- A GitHub account
- Git installed on your machine
- Basic knowledge of Git and GitHub

---

## 🚀 Quick Contribution Workflow

> Repeat this flow each time you want to work on a new feature or fix.

---

### 1️⃣ Fork the Repository

Click the **Fork** button at the top right of [the main repo](https://github.com/apaleblueman/whattheshell).

---

### 2️⃣ Clone Your Fork

```bash
git clone https://github.com/<your-username>/whattheshell.git
cd whattheshell
````

---

### 3️⃣ Set Upstream Remote (Only Once)

This connects your forked repo to the original project so you can fetch updates.

```bash
git remote add upstream https://github.com/apaleblueman/whattheshell.git
git remote -v
```

You only need to do this once after cloning.

---

### 4️⃣ Sync Your Fork Before New Work

Before starting new work, always sync your local and remote fork:

```bash
git checkout main
git pull upstream main
git push origin main
```

---

### 5️⃣ Create a New Branch

```bash
git checkout -b feature/<your-feature-name>
```

💡 Name branches like `feature/xyz`, `bugfix/abc`, `docs/update-readme`, etc.

---

### 6️⃣ Make Your Changes

* Write your code
* Test it
* Follow the project’s structure and naming conventions

---

### 7️⃣ Stage and Commit

```bash
git add .
git commit -m "✨ Add: brief explanation of the change"
```

💬 Use [conventional commits](https://www.conventionalcommits.org/) when possible:

* `✨` for features
* `🐛` for bugfixes
* `📝` for docs
* `♻️` for refactoring
* `🚀` for performance
* `🔧` for config
* `🔥` for removed code

---

### 8️⃣ Push to Your Fork

```bash
git push origin feature/<your-feature-name>
```

---

### 9️⃣ Open a Pull Request (PR)

* Go to your forked repo on GitHub
* Click **Compare & pull request**
* Fill in title and description
* Submit!

⛔ Do **not** merge your own PR — wait for review by the maintainer.

---

## 🔁 Keeping Your Fork Updated

Keep your fork in sync to avoid conflicts:

```bash
git checkout main
git pull upstream main
git push origin main
```

---

## 🧹 After PR is Merged

If your PR is accepted and merged:

### 🔨 Delete the local branch

```bash
git branch -d feature/<your-feature-name>
```

### 🔄 Start fresh next time

Repeat the **sync → branch → commit → PR** cycle for each new contribution.

---

## ❓ FAQ

### ❓ Can I just clone instead of forking?

🔐 No. Contributors must fork. Direct push access is not allowed for security and review purposes.

---

### ❓ What is a merge commit?

A merge commit is a special commit Git makes when combining branches. It's not bad, but we try to keep history clean. Maintainers may **squash and merge** your commits into one.

---

## 🧪 Example Workflow

```bash
# One-time setup
git clone https://github.com/<your-username>/whattheshell.git
cd whattheshell
git remote add upstream https://github.com/apaleblueman/whattheshell.git

# Before each new task
git checkout main
git pull upstream main
git push origin main
git checkout -b feature/your-feature

# Work...
# Add, commit, push
git push origin feature/your-feature

# Create PR on GitHub
```

---

## 📜 License

By contributing, you agree to license your code under the [MIT License](LICENSE).

---

## 🎉 Thanks!

Your contribution is appreciated. Let's make WhatTheShell awesome together!

```



