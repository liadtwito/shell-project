#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <libgen.h>
#include <sys/wait.h>

#define SIZE_BUFF 1024

void welcome();
// **welcome()** 
// The function prints a decorative ASCII art representing a welcome message. 
// It creates a visually pleasing display using characters to form patterns and shapes.
// The message likely serves as a visual indicator to the user 
// that they have entered a specific environment or program.

char* getInputFromUser();
// **getInputFromUser()**
// Reads input from the user until a newline character is encountered.
// It dynamically allocates memory for a character array to store the input.
// Then, it iterates over each character input by the user using getchar(),
// storing them in the dynamically allocated array. If needed, it reallocates memory
// to accommodate additional characters. If memory allocation fails at any point,
// it frees the previously allocated memory and returns NULL.
// Once the newline character is encountered, it terminates the string with '\0'
// and returns the dynamically allocated string containing the user input.

char** splitArgument(char*);
// **splitArgument()**
// Splits a string into tokens based on a delimiter and returns an array of pointers to tokens.
// The function takes a string (str) as input and tokenizes it using the custom my_strtok() function.
// It uses a dynamic array to store the tokens and reallocates memory as needed to accommodate more tokens.
// The initial size of the dynamic array is set to 2, assuming at least one token.
// It then iterates through the string, extracting tokens using my_strtok() and storing them in the array.
// The function returns a pointer to the array of tokens, with a NULL pointer at the end
// to signify the end of the token list.
// Note: The flag check_quotes is set to 1 in my_strtok() to handle quoted substrings.
// This ensures that substrings enclosed in double quotes are treated as single tokens.

void getLocation();
// **getLocation()**
//  The function retrieves and prints the current username and working directory.
//  It first attempts to obtain the username using the getlogin() function. 
//  If that fails, it tries alternative methods such as getenv("USER") and getenv("LOGNAME"). 
//  Then, it fetches the current working directory using getcwd(). 
//  Finally, it prints the username and location in a formatted prompt similar to what you'd see in a terminal,
//  ready for the user to input commands. 
//  This function essentially sets up the environment 
//  for command execution by providing contextual information about the user's session.

void logout(char* input);
// **logout()**
// Logs out the user if the input contains the word "exit".
// It converts the input to lowercase using the tolower() function
// to ensure case-insensitive comparison. Then, it checks if the lowercase input
// contains the substring "exit" using strstr(). If found, it frees the memory allocated for the input
// and prints "logout" before exiting the program with EXIT_SUCCESS.
// Otherwise, it simply frees the memory allocated for the input.

void cd(char **args);
// **cd()**
// Changes the current working directory.
// The function takes an array of strings (path) as input.
// It checks if the second element of the path array is NULL, indicating too many arguments,
// and prints an error message if so.
// Then, it attempts to change the directory to the specified path using the chdir() function.
// If the operation fails, it prints an error message indicating that the specified directory does not exist.

void cp(char **path);
// **cp()**
// Copies the contents of one file to another.
// Takes an array of strings (arguments) as input, where arguments[1] is the source file and arguments[2] is the destination file.
// It opens the source file in read mode and the destination file in write mode.
// If either file fails to open, it prints an error message and returns.
// Then, it reads characters from the source file and writes them to the destination file until the end of file (EOF) is reached.
// Finally, it closes both files.

void echo(char **arguments);
// **echo()**
// Prints the given arguments to the standard output.
// Takes an array of strings (arguments) as input.
// Iterates through the arguments and prints each one followed by a space.
// Finally, prints a newline character to complete the line.

void delete(char **path);
// **delete()**
// Deletes the specified file.
// Takes an array of strings (path) as input, where the first element is expected to be the file path.
// Checks if the file name is provided; if not, prints an error message and returns.
// Resolves the absolute path of the file using realpath().
// If the resolved path is NULL, prints an error message indicating that the file or directory does not exist.
// Otherwise, attempts to delete the file using unlink().
// If deletion fails, prints an error message indicating that the file or directory does not exist.
// Frees the memory allocated for the resolved path.

void mypipe(char **argv1, char **argv2);
// **mypipe()**
// Implements a simple pipe between two commands.
// Takes two arrays of strings (argv1 and argv2) as input, representing the commands to be piped.
// Creates a pipe using the pipe() system call.
// Forks a child process to execute the first command (argv1).
// Within the child process, redirects standard output to the write end of the pipe.
// Closes unnecessary file descriptors.
// Executes the first command (argv1) using execvp().
// Forks another child process to execute the second command (argv2).
// Within the child process, redirects standard input to the read end of the pipe.
// Closes unnecessary file descriptors.
// Executes the second command (argv2) using execvp().
// This function enables communication between two commands by redirecting the output of the first command
// to the input of the second command via a pipe.

void splitInputForPipe(char *input, char ***argv1, char ***argv2);
// **splitInputForPipe()**
// Splits the input command string into two separate command arrays for piping.
// Takes the input command string (input) and two double-pointer arrays to store the arguments for each command (argv1 and argv2).
// Searches for the pipe character ('|') in the input string to determine the separation between the two commands.
// If no pipe character is found, the function returns without splitting the input.
// Divides the input string at the pipe character position to obtain the first and second command strings.
// Parses each command string to extract individual arguments using the custom my_strtok() function.
// Allocates memory dynamically to store the arguments for each command.
// Constructs arrays of arguments for each command, terminated with a NULL pointer.
// Assigns the arrays of arguments to the pointers passed as arguments (argv1 and argv2).
// This function enables splitting a single input command containing a pipe character into two separate commands,
// each represented by an array of arguments, ready for execution.

char* my_strtok(char *str, const char delim,int check_quotes);
// **my_strtok()**
// A custom implementation of the strtok() function to tokenize a string.
// It takes three parameters: the input string to tokenize (str), the delimiter character (delim),
// and a flag (check_quotes) indicating whether to consider quoted substrings as single tokens.
// The function maintains state across multiple calls using static variables.
// On the first call (when str is not NULL), it initializes the tokenization process
// by setting the input string and the check_quotes flag. It returns the first token.
// On subsequent calls (when str is NULL), it continues tokenization from where it left off
// in the previous call, using the saved state. It returns the next token.
// The function handles quoted substrings if the check_quotes flag is set.
// It skips leading delimiters and returns consecutive non-delimiter characters as tokens.
// If the next token is quoted, it extracts the quoted substring as a single token.
// The function updates the next_token pointer to remember the position for the next call.
// It returns NULL when there are no more tokens to extract.

char* concatenateStrings(char** arguments,int size);
// **concatenateStrings()**
// Concatenates an array of strings into a single string.
// The function takes an array of strings (arguments) and its size as input.
// It allocates memory for a temporary string (temp) and initializes it with the first string in the array.
// Then, it iterates through the remaining strings in the array, appending each string to temp with a space in between.
// Memory reallocation is performed as needed to accommodate the growing string.
// When reaching the last string, the function removes the trailing space by replacing it with a null terminator.
// Finally, it returns a pointer to the concatenated string.

void move(char **args);
// **move()**
// Moves a file from a source location to a destination location.
// Takes an array of arguments (args) containing the source and destination paths.
// Checks if the necessary arguments are provided. If not, prints usage instructions and returns.
// Resolves the absolute path of the source file using realpath().
// If the source path resolution fails, prints an error message and returns.
// Resolves the absolute path of the destination file/directory.
// If the destination path resolution fails, prints an error message, frees memory, and returns.
// Checks if the destination is a directory. If so, appends the source file name to the destination path.
// If the resulting destination path is too long, prints an error message, frees memory, and returns.
// Moves the file using the rename() function.
// If the move operation fails, prints an error message. Otherwise, prints a success message.
// Frees memory allocated for the source path.

void echoppend(char **arguments);
// **echoppend()**
// Appends text to the end of a file.
// Takes an array of arguments (arguments) containing the text to append and the file path.
// Calculates the size of the arguments array to determine the number of arguments.
// Opens the file in append mode using fopen(). If the file opening fails, prints an error message and returns.
// Iterates through the arguments array starting from the second element (excluding the last two elements).
// Writes each argument followed by a space to the file using fprintf().
// Writes a newline character at the end of the appended text.
// Closes the file using fclose().

void echorite(char **arguments);
// **echowrite()**
// Writes text to a file, overwriting its contents if it already exists.
// Takes an array of arguments (arguments) containing the text to write and the file path.
// Calculates the size of the arguments array to determine the number of arguments.
// Opens the file in write mode using fopen(). If the file opening fails, prints an error message and returns.
// Iterates through the arguments array starting from the second element (excluding the last two elements).
// Writes each argument followed by a space to the file using fprintf().
// Writes a newline character at the end of the written text.
// Closes the file using fclose().

void readfile(char **arguments);
// **readfile()**
// Reads and prints the contents of a file to the standard output.
// Takes an array of arguments (arguments) containing the file path.
// Checks if the file path is provided as the first argument and there are no additional arguments.
// If not, prints an error message and returns.
// Opens the file in read mode using fopen(). If the file opening fails, prints an error message and returns.
// Reads each character from the file using fgetc() until the end of file (EOF) is reached.
// Prints each character to the standard output using putchar().
// Closes the file using fclose().
void wordCount(char **arguments);
// **wordCount()**
// Counts the number of words or lines in a file and prints the result.
// Takes an array of arguments (arguments) containing options and the file path.
// Checks if the required arguments are provided and if there are no extra arguments.
// If not, prints an error message and returns.
// Opens the file in read mode using fopen(). If the file opening fails, prints an error message and returns.
// Reads each character from the file using fgetc().
// Counts words by detecting transitions from whitespace to non-whitespace characters.
// Counts lines by detecting newline characters.
// Prints the count based on the specified option ("-w" for words, "-l" for lines).
// If an invalid option is provided, prints an error message.
// Closes the file using fclose().
