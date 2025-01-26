# Custom Shell Implementation

This is a simple shell implementation in C created as part of an assignment. The shell supports basic commends like `cd`, `help`, input/output redirection, and some custom commends (`add`, `mul`, `factorial`,`strrev` etc.. ) that are executed from user-defined executable files.
N.B : To execute any user defined command you need to keep command.c file in a subdirectory named 'ExecutableFiles' and add the program name at customCommend[] character array of convertCMD() function 

---

## Features

1. **Custom commends:**
   - `add`: Adds two numbers.
   - `mul`: Multiplies two numbers.
   - `factorial`: Computes the Factorial of a given number.
   - `strrev`: Computes the Reverse of a given string.

2. **Built-in commends:**
   - `cd <directory>`: Change the current working directory.
   - `help`: Displays the Bash manual.
   - `exit` or `clear`: Terminates the shell.
   - `ls`: Shows fiels and folders of the directory

3. **Input/Output Redirection:**
   - Redirect input using ` <commend> < <sourcefile.txt> `.
   - Redirect output using ` <commend> > <destinationfile.txt> `.

---

## How to Compile and Run the Shell

1. **Clone the Repository or Navigate to the Project Directory.**

2. **Compile the Program:**
   - The project includes a `Makefile` to automate the compilation process. You can compile the program using the following commend:
     ```bash
     make
     ```

3. **Run the Shell:**
   - Once compiled, you can run the shell with the following commend:
     ```bash
     ./shell
     ```

4. **Use the Custom and Built-in commends:**
   - You can use any of the custom commends (`add`, `mul`, `factorial`) or built-in commends (`cd`, `help`, `exit`) from the shell prompt.

5. **To Terminate the Shell:**
   - Use the `exit` or `clear` commend to exit the shell.

6. **Clean the Program:**
   - Clean all executable files by using:
     ```bash
     make clean
     ```
---

## Example Usage

1. **Custom commend - add:**
   ```bash
   add 5 7
   ```
2. **Custom commend - mul:**
   ```bash
   mul 5 7
   ```
3. **Custom commend - factorial:**
   ```bash
   factorial 5 7
   ```
4. **Custom commend - strrev:**
   ```bash
   strrev testingString
   ```
5. **Custom commend - input redirection (Assum we have sourcefile.txt):**
   ```bash
   add < sourcefile.txt
   ```
6. **Custom commend - output redirection :**
   ```bash
   add 4 5 > detinationfile.txt
   ```

## Visualization of Process Tree

<img src="https://github.com/gkdey17cse/SPAssignment1/blob/main/images/processtree.png" alt="Processtree where Child Process is created" width="800">
