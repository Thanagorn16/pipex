# 🚰 Pipex
Pipex is a Unix-based C program that replicates shell pipelines:
It takes an input file, passes its content through a series of commands, and outputs the result to a file — just like how piping works in the terminal.

>📌 Goal: Understand process creation, piping, and file descriptor manipulation in Unix.

## 🧠 Project Description
Pipex simulates this shell behavior:
```bash
< file1 cmd1 | cmd2 > file2
```
Your command-line input is parsed, and a pipe is created to pass data between commands using child processes and system calls like fork, execve, pipe, and dup2.

## 🔧 Why C and Unix System Calls?
- Low-level control over memory and processes.

- Real-world experience working with the kernel via syscalls.

- Builds a strong foundation for systems and backend programming.

## ⚠️ Challenges Faced
- Managing multiple processes and file descriptors safely.

- Dealing with command parsing and path resolution.

- Implementing robust error handling and resource cleanup.

--- 

# 📚 Table of Contents

- [📦 Installation](#-installation)
- [▶️ Usage](#️-usage)
- [💡 Examples](#-examples)
- [📝 Notes](#-notes)

## 📦 Installation

Clone this repo:
```bash
git clone https://github.com/Thanagorn16/pipex.git
cd pipex
```

Compile the project:
```bash
make
```

---

## ▶️ Usage

```bash
./pipex infile "command1" "command2" outfile
```
This mimics:
```bash
< infile command1 | command2 > outfile
```

## 📂 Arguments:

`infile` – The file you want to read from.

`command1` – First command (reads from infile).

`command2` – Second command (writes to outfile).

`outfile` – The file where the output is saved.

---

## 💡 Examples

__Count lines in a file:__

```bash
./pipex input.txt "cat" "wc -l" output.txt
```

__Search and sort:__
```bash
./pipex logs.txt "grep -i error" "sort" result.txt
```
__With paths:__

```bash
./pipex input.txt "/bin/ls -l" "/usr/bin/grep pipex" output.txt
```

---

## 📝 Notes
- ❗Commands must be enclosed in quotes if they include arguments.

- 🧪 Tested on macOS and Linux (Ubuntu).

- 🔍 Make sure your environment variables (like $PATH) are correctly set, as execve depends on them.

- 🧼 Resources (files, pipes) are cleaned up properly on exit or error.
