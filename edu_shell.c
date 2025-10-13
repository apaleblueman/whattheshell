#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_TOKENS 128
#define MAX_CMDS 16
#define PROMPT_SIZE 1024
#define CWD_MAX 1000  // Limit cwd to avoid snprintf warnings

typedef struct {
    char *argv[MAX_TOKENS];
    char *infile;
    char *outfile;
    int append;
} Command;

typedef struct {
    const char *cmd;
    const char *hint;
} CmdHint;

// Teacher mode command hints
CmdHint hints[] = {
    {"ls", "Lists files and directories. Use -l for detailed info."},
    {"cd", "Changes the current directory. Example: cd /path/to/dir"},
    {"pwd", "Prints the current working directory."},
    {"echo", "Prints text to the terminal. Example: echo Hello"},
    {"cat", "Displays file contents. Can be combined with pipes."},
    {"grep", "Filters input lines matching a pattern. Example: grep 'text' file"},
    {"mkdir", "Creates a new directory. Example: mkdir mydir"},
    {"rmdir", "Removes an empty directory."},
    {"rm", "Removes files or directories. Use with caution."},
    {"touch", "Creates an empty file or updates timestamps."},
    {"cp", "Copies files or directories."},
    {"mv", "Moves or renames files or directories."},
    {NULL, NULL}
};

int teacher_mode = 0;

// Signal handler for Ctrl+C
void sigint_handler(int sig) {
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
}

// Tokenizer
char **tokenize(const char *s) {
    char *buf = strdup(s);
    char **tokens = calloc(MAX_TOKENS, sizeof(char *));
    int ti = 0;
    char *p = buf;
    while (*p) {
        while (*p && (*p == ' ' || *p == '\t' || *p == '\n')) p++;
        if (!*p) break;
        char *start = p;
        while (*p && *p != ' ' && *p != '\t' && *p != '\n') p++;
        if (*p) *p++ = '\0';
        tokens[ti++] = strdup(start);
    }
    tokens[ti] = NULL;
    free(buf);
    return tokens;
}

// Parse single command segment
Command parse_segment(char *segment) {
    Command c = { .argv = {NULL}, .infile = NULL, .outfile = NULL, .append = 0 };
    char **tokens = tokenize(segment);
    int ti = 0;
    for (int i = 0; tokens[i]; i++) {
        if (strcmp(tokens[i], "<") == 0) {
            if (tokens[i + 1]) c.infile = strdup(tokens[++i]);
        } else if (strcmp(tokens[i], ">") == 0) {
            if (tokens[i + 1]) { c.outfile = strdup(tokens[++i]); c.append = 0; }
        } else if (strcmp(tokens[i], ">>") == 0) {
            if (tokens[i + 1]) { c.outfile = strdup(tokens[++i]); c.append = 1; }
        } else {
            c.argv[ti++] = strdup(tokens[i]);
        }
    }
    c.argv[ti] = NULL;
    for (int i = 0; tokens[i]; i++) free(tokens[i]);
    free(tokens);
    return c;
}

// Parse full line with pipes
int parse_line(char *line, Command cmds[]) {
    int ci = 0;
    char *save;
    char *seg = strtok_r(line, "|", &save);
    while (seg && ci < MAX_CMDS) {
        cmds[ci++] = parse_segment(seg);
        seg = strtok_r(NULL, "|", &save);
    }
    return ci;
}

// Print command hint
void print_hint(const char *cmd) {
    for (int i = 0; hints[i].cmd; i++) {
        if (strcmp(hints[i].cmd, cmd) == 0) {
            printf("\033[36m[HINT]\033[0m %s\n", hints[i].hint);
            break;
        }
    }
}

// Execute commands with pipes/redirection
void execute_commands(Command cmds[], int ncmds) {
    int pipes[MAX_CMDS - 1][2];
    pid_t pids[MAX_CMDS];

    for (int i = 0; i < ncmds - 1; i++)
        if (pipe(pipes[i]) < 0) { perror("pipe"); exit(1); }

    for (int i = 0; i < ncmds; i++) {
        // Teacher mode trace BEFORE fork
        if (teacher_mode) {
            printf("\033[33m[TRACE]\033[0m Executing command: ");
            for (int k = 0; cmds[i].argv[k]; k++)
                printf("%s ", cmds[i].argv[k]);
            printf("\n");
            if (cmds[i].infile)
                printf("\033[36m[INFO]\033[0m Input redirected from: %s\n", cmds[i].infile);
            if (cmds[i].outfile)
                printf("\033[36m[INFO]\033[0m Output redirected to: %s\n", cmds[i].outfile);
            if (ncmds > 1)
                printf("\033[36m[INFO]\033[0m Command is part of a pipe sequence\n");
            if (cmds[i].argv[0]) print_hint(cmds[i].argv[0]);
        }

        pid_t pid = fork();
        if (pid == 0) {
            if (cmds[i].infile) {
                int fd = open(cmds[i].infile, O_RDONLY);
                if (fd < 0) perror("open infile");
                else { dup2(fd, STDIN_FILENO); close(fd); }
            }
            if (cmds[i].outfile) {
                int fd = open(cmds[i].outfile,
                              O_WRONLY | O_CREAT | (cmds[i].append ? O_APPEND : O_TRUNC),
                              0644);
                if (fd < 0) perror("open outfile");
                else { dup2(fd, STDOUT_FILENO); close(fd); }
            }

            if (i > 0) dup2(pipes[i - 1][0], STDIN_FILENO);
            if (i < ncmds - 1) dup2(pipes[i][1], STDOUT_FILENO);

            for (int j = 0; j < ncmds - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            execvp(cmds[i].argv[0], cmds[i].argv);
            perror("execvp");
            exit(1);
        } else if (pid > 0) {
            pids[i] = pid;
        } else {
            perror("fork");
            exit(1);
        }
    }

    for (int i = 0; i < ncmds - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < ncmds; i++)
        waitpid(pids[i], NULL, 0);
}

// Built-in help
void print_help() {
    printf("edu-shell Help:\n");
    printf("Built-in commands:\n");
    printf("  cd [dir]      Change directory (default: HOME)\n");
    printf("  history       Show command history\n");
    printf("  help          Show this help\n");
    printf("  exit          Exit the shell\n");
    printf("Teacher mode:\n");
    printf("  teacher on/off Toggle teacher mode with command tracing and hints\n");
    printf("Supports external commands, pipes (|), and redirection (<, >, >>)\n");
}

int main(void) {
    signal(SIGINT, sigint_handler);

    using_history();
    read_history(".edu_shell_history");

    while (1) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        char prompt[PROMPT_SIZE];
        snprintf(prompt, sizeof(prompt), "[%.1000s] edu-shell> ", cwd);

        char *line = readline(prompt);
        if (!line) continue;
        if (!*line) { free(line); continue; }

        add_history(line);
        write_history(".edu_shell_history");

        // Built-in commands
        if (strcmp(line, "exit") == 0) { free(line); break; }

        if (strncmp(line, "cd", 2) == 0) {
            char *dir = strtok(line + 2, " \t\n");
            if (!dir) dir = getenv("HOME");
            if (chdir(dir) != 0) perror("cd");
            free(line);
            continue;
        }

        if (strcmp(line, "history") == 0) {
            HIST_ENTRY **hist_list = history_list();
            if (hist_list) {
                for (int i = 0; hist_list[i]; i++)
                    printf("%d  %s\n", i + history_base, hist_list[i]->line);
            }
            free(line);
            continue;
        }

        if (strcmp(line, "help") == 0) {
            print_help();
            free(line);
            continue;
        }

        if (strncmp(line, "teacher", 7) == 0) {
            if (strstr(line, "on")) { teacher_mode = 1; printf("\033[32m[Teacher Mode Enabled]\033[0m\n"); }
            else if (strstr(line, "off")) { teacher_mode = 0; printf("\033[31m[Teacher Mode Disabled]\033[0m\n"); }
            else { printf("Usage: teacher [on|off]\n"); }
            free(line);
            continue;
        }

        Command cmds[MAX_CMDS];
        int ncmds = parse_line(line, cmds);
        execute_commands(cmds, ncmds);

        // Free command memory
        for (int i = 0; i < ncmds; i++) {
            for (int j = 0; cmds[i].argv[j]; j++) free(cmds[i].argv[j]);
            if (cmds[i].infile) free(cmds[i].infile);
            if (cmds[i].outfile) free(cmds[i].outfile);
        }
        free(line);
    }

    return 0;
}
