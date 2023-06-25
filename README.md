The simple shell project much like the printf project is another alx program effort towards strengthening students' collaboration skills.

For this project, team members are encouraged to research and implement resources that can guide them in completing a simple shell that models the UNIX command line interpreter (CIL).

This project supports some common shell commands like the cat, pwd, ls... We have included amongst the files, a man page that summarizes our version of the simple shell for this project.

**Project tasks summary:**

**C - Simple Shell**

/** Mandatory Tasks **/

**Task 0** - Write a beautiful code that passes the Betty checks

**Task 1** - Write a UNIX command line interpreter.

**Task 2** - Simple shell 0.1 +
- Handle command lines with arguments

**Task 3** - Simple shell 0.2 +
- Handle the Path
- Fork must not be called if the command doesn’t exist

**Task 4** - Simple shell 0.3 +
- Implement the exit built-in, that exits the shell
- Usage: exit
- You don’t have to handle any argument to the built-in exit

**Task 5** - Simple shell 0.4 +
- Implement the env **built in**, that prints the current environment

/** Advanced Tasks **/

**Task 6** - Simple shell 0.1 +
- Write your own get line function
- Use a buffer to read many chars at once and call the least possible the read system call
- You will need to use static variables
- You are not allowed to use getline
- You don’t have to:
- be able to move the cursor

**Task 7** - Simple shell 0.2 +
- You are not allowed to use strtok

**Task 8** - Simple shell 0.4 +
- handle arguments for the built-in exit
- Usage: exit status, where status is an integer used to exit the shell

**Task 9** - Simple shell 1.0 +
- Implement the setenv and unsetenv builtin commands

**Task 10** - Simple shell 1.0 +
- Implement the builtin command cd:

**Task 11** - Simple shell 1.0 +
- Handle the commands separator ;


**Task 12** -Simple shell 1.0 +
- Handle the && and || shell logical operators


**Task 13** - Simple shell 1.0 +
- Implement the alias builtin command
- Usage: alias [name[='value'] ...]


**Task 14** - Simple shell 1.0 +
- Handle variables replacement
- Handle the $? variable
- Handle the $$ variable

**Task 15** - Simple shell 1.0 +
- Handle comments (#)

**Task 16** - Simple shell 1.0 +
- Usage: simple_shell [filename]
- Your shell can take a file as a command line argument
- The file contains all the commands that your shell should run before exiting
- The file should contain one command per line
- In this mode, the shell should not print a prompt and should not read from stdin
