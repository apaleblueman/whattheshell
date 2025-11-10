### **Repository Name:** `WhatTheShell`

**Description:**

> 🐚 *WhatTheShell* is a custom Unix-like shell built in C that replicates essential command-line operations while introducing an optional **Teacher Mode** for real-time educational feedback. It supports command execution, piping, I/O redirection, process handling, and built-in commands like `cd`, `history`, and `help`. Designed for both practical use and academic learning, it bridges the gap between shell interaction and OS-level understanding.

**Key Features:**

* POSIX-compliant shell with `fork()`, `execvp()`, and `waitpid()` system calls
* Built-in command parsing, error handling, and signal management
* Support for **pipes**, **I/O redirection**, and **multiple commands**
* **Teacher Mode** — explains each system call and process during execution
* Persistent command history using GNU Readline
* Modular C architecture for easy extensibility

**Planned Enhancements:**

* Command auto-completion and syntax highlighting
* Resource profiling (CPU/RAM usage tracking)
* Support for background job control (`&`)

**Usage Example:**

```bash
[~/projects] whattheshell> ls | grep .c > output.txt
[TRACE] Executing command: ls
[INFO] Output redirected to: output.txt
```
**License:** MIT License

---

Would you like me to also generate a shorter **GitHub tagline (one-liner)** version for the repo header (under 120 characters)? It’s perfect for the repo summary line.
