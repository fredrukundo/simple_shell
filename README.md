# Simple Shell Project

This project is a simple shell implementation created as part of the ALX Software Engineering program. The shell supports basic command execution, environment variable management, and built-in commands. Below is an overview of the key components and functionalities of the shell.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [File Structure](#file-structure)
- [Usage](#usage)
- [Building](#building)
- [Known Issues](#known-issues)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The simple shell project is a basic shell that supports command execution, environment variable management, and built-in commands. It provides a minimalistic shell environment with essential functionalities.

## Features

- Basic command execution
- Environment variable management
- Built-in commands support
- Signal handling for SIGINT

## File Structure

The project consists of a single header file `shell.h` that contains all the necessary declarations, structures, and function prototypes. The file is organized into several sections:

- **Data Structures:** Structures for representing data used by the shell.
- **Function Prototypes:** Declarations for functions used throughout the project.
- **Utility Functions:** Various utility functions for string manipulation, memory allocation, and error handling.
- **Built-in Commands:** Implementation of built-in commands such as `cd`, `exit`, `env`, etc.
- **Main Execution Loop:** The main loop for reading and executing commands.
- **Error Handling:** Functions for handling errors and displaying error messages.
- **Help Functions:** Functions providing help information for shell commands.

## Usage

To use the simple shell, compile the source code and run the executable. The shell will provide a prompt where you can enter commands.

```bash
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
$ ./hsh
