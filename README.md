# Minishell

![42 Badge](https://img.shields.io/badge/42-Project-black?style=flat-square&logo=42)
![Language C](https://img.shields.io/badge/Language-C-blue?style=flat-square)

> *As beautiful as a shell.*

**Minishell** is a project from the [42 Network](https://42.fr/en/homepage/) common core curriculum. The objective of this project is to create a simple, yet fully functional shell (command-line interpreter) from scratch using C. By building Minishell, we dive deep into processes, file descriptors, signals, and the robust parsing of user input.

## Features

This project faithfully reproduces many core features of `bash`:

- **Prompt**: Displays a prompt when waiting for a new command.
- **Command Execution**: Finds and executes executables based on the `PATH` environment variable or using relative/absolute paths.
- **Built-in Commands**:
  - `echo` with option `-n`
  - `cd` with only a relative or absolute path
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options
- **Redirections**:
  - `<` redirect input.
  - `>` redirect output.
  - `<<` read input until a delimiter is seen (heredoc).
  - `>>` redirect output in append mode.
- **Pipes (`|`)**: Connects the output of one command to the input of the next.
- **Environment Variables**: Expands environment variables (`$VAR`).
- **Exit Status**: Expands `$?` to the exit status of the most recently executed foreground pipeline.
- **Quoting**:
  - Single quotes (`'`) prevent the shell from interpreting meta-characters and environment variables.
  - Double quotes (`"`) prevent interpretation of meta-characters but allow `$VAR` expansion.
- **Signal Handling**: Correct handling of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`. The shell doesn't quit unexpectedly and behaves like `bash`.

## Architecture & Approach

Our minishell implementation relies on a robust internal structure:

1. **Lexical Analysis (Tokenizer)**: The shell reads the raw user input and splits it into manageable pieces called *tokens* (words, operators, quotes, etc.).
2. **Parsing (Automaton & AST)**: Tokens are validated against grammatical rules. We use an **Abstract Syntax Tree (AST)** to structure the commands, manage operator precedence (e.g. pipes vs. redirections), and handle execution flows efficiently.
3. **Expansion & Unquoting**: Variables inside double quotes or standard strings are evaluated and expanded. Syntactic quotes are stripped away.
4. **Execution**: The shell walks the AST. For individual commands, it calls system programs (via `execve()`) or executes built-ins. Pipes (`|`) trigger multiple child processes linked by file descriptors.
5. **Memory Management**: Meticulous garbage collection and free functions ensure no memory leaks during execution.

## Project Structure

```
.
├── AST/                # Parsing into Abstract Syntax Tree
├── all_libft/          # Extended libft (libft, get_next_line, ft_printf)
├── exec/               # Execution logic, pipe handling, and multi-processes
│   └── built-ins/      # Implementation of cd, echo, env, exit, export, pwd, unset
├── expand_unquote/     # Environment variable expansion and quote removal
├── heredoc/            # Handling of the << heredoc redirection
├── includes/           # Header files (minishell.h, ast.h, types.h, etc.)
├── parsing/            # Lexer/Tokenizer and Automaton logic
├── signals.c           # Signal handlers (SIGINT, SIGQUIT)
└── main.c              # Entry point and Main prompt loop
```

## Usage

### Installation

Clone the repository and compile using `make`:
```bash
git clone https://github.com/your-username/mini-shell.git
cd mini-shell
make
```

### Running

Start the shell by running the compiled executable:
```bash
./minishell
```

You will be greeted with the custom prompt. You can now type your commands, set environment variables, or run scripts using pipelines!

## License & Credits

This project was built by **leogarci** (`leogarci@student.42.fr`) as part of the 42 curriculum.

The code complies with the strict standard of the *42 Norm*, focusing on clean architecture, defensive programming, and memory leak prevention.