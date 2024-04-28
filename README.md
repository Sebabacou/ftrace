# Project: Ftrace

## Overview
Ftrace is a Unix System Programming project developed for the B-PSU-400 course. The program enables the analysis of executables by tracing various elements including system calls, internal function calls, signals received, and function calls from shared libraries. The output is formatted to provide insights into the execution flow of the program.

## Project Details
- **Project Number:** B-PSU-400
- **Project Name:** ftrace
- **Version:** 3.1
- **Binary Name:** ftrace
- **Language:** C
- **Compilation:** Makefile with rules for re, clean, and fclean
- **Platform:** x86-64/Linux
- **Libraries Allowed:** libc, libelf, libm

## Features
- **Tracing Elements:** Ftrace traces and displays the following elements:
  - System calls
  - Internal function calls with their respective names and addresses
  - Signals received from other programs
  - Function calls contained in shared libraries (.so)

## Usage
```bash
./ftrace <command>
