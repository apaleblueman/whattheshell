#whattheshell- a custom shell project
---
this project aims to build a custom shell in C.
It will implement various features in these phases:
Introduction

This project is an implementation of a custom Unix-like command-line shell written in C. Beyond executing standard system commands, this shell includes a unique "educational mode." When activated, this mode provides real-time, low-level explanations of the operating system concepts at play, such as process creation and I/O redirection, making it a powerful tool for learning.
Features

This shell is designed to be built incrementally, from simple basics to complex features.

Phase 1: Foundations

    REPL Loop: A continuous Read-Eval-Print-Loop to process user commands.

    Basic Command Execution: Uses fork() and execvp() to execute external programs.

    Educational Mode Toggle: A simple built-in command to turn the learning mode on and off.

    Basic Explanations: Provides fundamental explanations for fork(), execvp(), and waitpid().

Phase 2: The Core

    Input Parsing: Handles user input and tokenizes it into commands and arguments.

    I/O Redirection: Supports input (<) and output (>) redirection to and from files.

    Pipes: Implements piping (|) to connect the output of one command to the input of another.

    Built-in Commands: Includes a built-in cd command for changing the current directory, which is necessary as execvp() cannot handle it.

Phase 3: Refinement

    Robust Error Handling: Provides meaningful error messages for issues like "command not found" or file permissions.

    Signal Handling: Gracefully handles signals like SIGINT (Ctrl+C).
   
