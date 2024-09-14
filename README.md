# Minishell

## Description

The Minishell project was developed as part of the Software Engineering course, with the goal of creating a simplified version of a Unix shell. It allows the execution of basic system commands, handling of redirections and pipes, and managing environment variables. It also implements built-in functions that simulate the behavior of a real shell, but with predefined functionalities and constraints.
Features

* The Minishell supports the following features:
    * Basic Command Execution: Executes any command found in the system path (PATH), such as <kbd>ls</kbd>, <kbd>grep</kbd>, <kbd>cat</kbd>, etc.
    * Built-in Commands: Implemented internal commands:
        <kbd>echo</kbd>: Displays a line of text.
        <kbd>cd</kbd>: Changes the current directory.
        <kbd>pwd</kbd>: Prints the current working directory.
        <kbd>export</kbd>: Sets environment variables.
        <kbd>unset</kbd>: Removes environment variables.
        <kbd>env</kbd>: Displays the current environment variables.
        <kbd>exit</kbd>: Exits the shell.
    * Input and Output Redirection:
        Redirects input (<kbd><</kbd>) and output (<kbd>></kbd> or <kbd>>></kbd>) to/from files.
    * Pipes (<kbd>|</kbd>): Connects multiple commands, where the output of one command serves as the input for the next.
    * Signal Handling:
        <kbd>Ctrl+C</kbd>: Interrupts the current command, but does not exit the shell.
        <kbd>Ctrl+D</kbd>: Exits the shell.
        <kbd>Ctrl+\</kbd>: Ignored.
    * Environment Variables: Utilizes and modifies environment variables for command execution.
    * Process Management: Creates child processes for executing external commands.
    * Command Reading: Uses the <kbd>readline</kbd> function to capture and store command history.

Project Requirements

* The project was developed following these guidelines:

    * No Global Variables: All shell states are managed locally, adhering to good * practices of scope and modularity.
    * Memory Management: All memory usage is efficiently managed, preventing memory leaks. Tools like <kbd>valgrind</kbd> were used to ensure this integrity.
    * External Function Restrictions: The use of external functions is limited to a specific list, including <kbd>readline</kbd>, <kbd>malloc</kbd>, <kbd>free</kbd>, <kbd>write</kbd>, <kbd>fork</kbd>, <kbd>wait</kbd>, <kbd>waitpid</kbd>, <kbd>signal</kbd>, <kbd>kill</kbd>, <kbd>exit</kbd>, <kbd>getcwd</kbd>, <kbd>chdir</kbd>, among others.


## Project Structure

```bash
├── mandatory/
│   ├── builtins/
│   ├── redirect/
│   ├── lexer/
│   ├── token/
│   ├── parser/
│   └── utils/
├── include/
│   └── minishell.h
├── Libs
├── Makefile
└── README.md
```
* src/: Contains the project's source code.
    * builtins/: Implementation of the built-in commands.
    * lexer/: Functions responsible for validating the correct grammar for tokenization.
    * parser/: Functions responsible for parsing command lines.
    * redirect/: Functions responsible for creating the linked list of all redirects in the command line.
    * signals.c: Implementation of signal handling, such as <kbd>Ctrl+C</kbd> and <kbd>Ctrl+D</kbd>.
    * utils/: Utility functions used across different parts of the project.
    * include/: Contains header files (<kbd>.h</kbd>) for function and structure definitions.
    * Makefile: Used to compile the project.
    * README.md: This documentation file.

## Compilation and Execution
### Prerequisites

Ensure you have the following tools installed before compiling the project:
* <kbd>gcc</kbd>: C compiler.
* <kbd>make</kbd>: Build automation tool.
* <kbd>readline</kbd>: Library used for command-line input.

### Compilation
To compile Minishell, run the following command in the project's root directory:
```bash
bash
```

```bash
make
```
This will generate an executable called <kbd>minishell</kbd>.
### Execution

After compiling, you can run Minishell with the following command:
```bash
./minishell
```
You can then type commands in the shell, such as <kbd>ls</kbd>, <kbd>pwd</kbd>, or <kbd>echo Hello World</kbd>, just like in a traditional shell.

## Testing

During the project development and final evaluation, the following aspects were tested:
* Correct execution of built-in commands.
* Handling of redirections and pipes.
* Proper signal and memory management.
* Correct implementation of scripts and environment variable handling.

## Common Issues

* Command execution failure: Check the PATH and ensure the correct use of <kbd>fork</kbd> and <kbd>exec</kbd>.
* Segfaults or memory errors: Use tools like <kbd>valgrind</kbd> to identify memory leaks or invalid accesses.
* Improper signal handling: Ensure that signals like <kbd>Ctrl+C</kbd> and <kbd>Ctrl+D</kbd> are properly handled without abruptly closing the shell.

## References

The development of this project required a deep understanding of the following topics:

* Unix system programming.
* Process management in C.
* Terminal input and output manipulation.
* Memory management in C.
* Signal handling in Unix systems.

## Contribution

This project was developed as part of the common core at 42 São Paulo, and was done in collaboration with my amazing partner, Carol Kunimura, whom I admire greatly and from whom I learned so much. I also received invaluable help from several 42 colleagues, to whom I am immensely grateful for their many hours of dedication and late-night debugging: Beatriz Yoshimori, Davy Paulino, Lucas Santos, Ranna Leslie, and Renan Leite I love you all, <mark>THANK YOU!</mark>. 
This project was a pair challenge for educational purposes, and external contributions are not accepted. However, feel free to clone the repository and use it as a base for personal study.