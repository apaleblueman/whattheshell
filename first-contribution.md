# 📝 Team Activity: Your First Official Git Commit (Visitor Log)

Welcome, contributors! 🎉  
In this short activity, you’ll make your first official commit to our `whattheshell` GitHub repository by adding your name to the README file as a "visitor log".

This will help you practice making contributions using Git and GitHub **via CLI (Git Bash)**.

---

## ✅ Prerequisites

Before starting, ensure you have:

- Git installed and configured with your name/email
- GitHub account set up
- SSH authentication already working
- Repository cloned via SSH

If you're unsure about any of the above, contact the maintainer.

---

## 🛠️ Steps to Complete the Activity

### 1. Open Git Bash

Navigate to the folder where you cloned the repo.  
For example:

```bash
cd ~/whattheshell
```

### 2. Create a New Branch

Always work on a separate branch, not `main`!

```bash
git checkout -b visitor-log/john
```

Replace `john` with your name or GitHub username.

---

### 3. Edit the `README.md` File

Open the `README.md` file using a text editor (like VS Code or Notepad).

At the bottom (or in a section titled "Visitor Log"), add your name and date like this:

```markdown
## 👥 Visitor Log

- John Doe - Aug 2, 2025 ✅
```

Save the file.

---

### 4. Check Status and Stage the File

Check if your file was modified:

```bash
git status
```

Stage the change:

```bash
git add README.md
```

---

### 5. Commit Your Changes

Make a meaningful commit message:

```bash
git commit -m "Add John to Visitor Log"
```

---

### 6. Push Your Branch

```bash
git push -u origin visitor-log/john
```

Make sure you replace `john` with your actual branch name.

---

### 7. Create a Pull Request (PR)

Go to the repository on GitHub (https://github.com/apaleblueman/whattheshell)

- You'll see a prompt to open a **Pull Request**.
- Title: `Add John to Visitor Log`
- Description: "This is my first contribution via Git CLI 🎉"

Click **Create Pull Request**.

---

## 🔁 Reminder: Pull Before You Push (Every Time)

Before starting any new work or pushing again, always do:

```bash
git checkout main
git pull origin main
```

Then create a new branch from the latest `main`.

---

## 💡 Best Practices

- Never push directly to `main`
- Use your own branch for each task
- Commit messages should be short and meaningful
- Ask for help if you're unsure!

---

## 🎯 Goal of This Activity

✅ Practice Git basics (branching, commit, push, PR)  
✅ Ensure your environment is working  
✅ Build confidence in using CLI tools  
✅ Start contributing to `whattheshell`

---

