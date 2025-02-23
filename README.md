# Minishell

Minishell is a simple Unix shell written in C as part of the 42 School curriculum.  
It supports essential shell functionalities, including:  

- Command execution with pipes and redirections (`|`, `<`, `>`, `>>`)  
- Environment variable handling (`$VAR`)  
- Logical operators (`&&`, `||`) and parentheses for priority execution  
- Wildcard expansion (`*`) in the current directory  
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)  

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

## Collaborators

- [Valentin Catalin Bengea](https://github.com/vbengea)  
- [Juan Daniel Flores](https://github.com/juandfloresm)  

## License

This project is licensed under the [MIT License](LICENSE).  

