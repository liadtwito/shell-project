
#include "myFunctions.h"

typedef struct {
    char *command;
    void (*func)(char **);
} CommandFunc;

int main() {
    CommandFunc commands[] = {
        {"echo", echo},
        {"cd", cd},
        {"cp", cp}
    };

    int numCommands = sizeof(commands) / sizeof(CommandFunc);
    welcome();

    while (1) {
        getLocation();
        char *input = getInputFromUser();

        if (strcmp(input, "exit") == 0 || strncmp(input, "exit ", 5) == 0) {
            logout(input);
            free(input);
            break;
        }

        char **arguments = splitArgument(input);
        
        if (strchr(input, '|') != NULL) {
            char **argv1, **argv2;
            splitInputForPipe(input, &argv1, &argv2);
            mypipe(argv1, argv2);
            
            int status;
            while (wait(&status) > 0);

            for (int i = 0; argv1[i] != NULL; i++) {
                free(argv1[i]);
            }
            free(argv1);
            
            for (int i = 0; argv2[i] != NULL; i++) {
                free(argv2[i]);
            }
            free(argv2);
        } else {
            int found = 0;
            for (int i = 0; i < numCommands; i++) {
                if (strcmp(input, commands[i].command) == 0) {
                    commands[i].func(arguments);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Command not found: %s\n", input);
            }
        }
        free(arguments);
        free(input);
    }

    return 0;
}
