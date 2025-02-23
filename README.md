# Minishell

Minishell is a simple Unix shell written in C as part of the 42 School curriculum.  
It was built from scratch to mimic a real shell, focusing on system calls, process management,  
and input parsing. The project reinforced my knowledge of C, memory management, and UNIX 

## Features

- Command execution with pipes and redirections (`|`, `<`, `>`, `>>`, `<<`)  
- Environment variable handling (`$VAR`)  
- Logical operators (`&&`, `||`) and parentheses for priority execution  
- Wildcard expansion (`*`) in the current directory  
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)  
- Heredoc redirection (`<<`) for handling multi-line input  

## Installation

```sh
git clone git@github.com:vbengea/MiniShell.git
cd minishell
make
```

## Usage

Run the shell with:  

```sh
./minishell
```

Exit with `exit`.  

## Example

```sh
minishell$ echo Hello && (ls -l | grep minishell)
minishell$ cat *.c | wc -l
```

## What I Learned

- Deep understanding of UNIX system calls and process control  
- Implementing a tokenizer and parser for shell input  
- Managing memory efficiently to avoid leaks  
- Handling signals and terminal behaviors correctly  

## Collaborators

- [Valentin Catalin Bengea](https://github.com/vbengea)  
- [Juan Daniel Flores](https://github.com/juandfloresm)  

## License

This project is licensed under the [MIT License](LICENSE).  

