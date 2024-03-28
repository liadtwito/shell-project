#include "myFunctions.h"

void welcome() {
        printf("%s\n",
           "\n"
           "               ', , , ,\n"
           "              ' ' ' ' ' ' ' , , ,\n"
           "                               '  ',\n"
           "        ' ' ' ' , , ,                 ' ,\n"
           "                    ' '                 ' '  ',\n"
           "        ' .                ;                  ' ,\n"
           "           ' '        , ' '   '   '               ' ' ,.\n"
           "        '        ;  '               ' ' .          . '\n"
           "         ' .  '  '                         ' ' '   , '\n"
           "        , '   '   '   '   ' '    ' '   ' '  ' ' '     ;\n"
           "                      , '              , ,  , ; : ccccc ,.\n"
           "                , ' '           , , , , , , , ,  ' ' ' ** ; 1x0 .\n"
           "        . . . . . . . ' ' ' ' ' ' ' . . . . . . . . . . . . , . , : ld ;\n"
           "          . '                            . '  ; ; ; : : : ; , , . X ,              ,                 #\n"
           "        . '             . . . ' ' ' ' ' ' . .                    Oxxoc : , . ' ' '                   #\n"
           "                 , , , , , ,                                 , ONkC ;, ; cokOdc ',.                  #\n"
           "            , , ,                                         OMO                   ': ddo               #\n"
           "          , '                                           dMc                        : 00 ;            #\n"
           "        . '                                             OM .                         . : 0 .         #\n"
           "        '                                               ; Wd                                         #\n"
           "                                                           ; XO ,                                    #\n"
           "                                                               , doodlc ;, ..                        #\n"
           "                                                                    .. ' , ; : c                     #\n"
           "                                                                              . : d ; .              #\n"
           "                                                                                     'd ,            #\n"
           "                                                                                         ; l         #\n"
           "                        __                             __  ______                        .0          #\n"
           "         _      _____  / /________  ____ ___  ___     / / /_  __/                        .0'         #\n"
           "        | | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\   / /   / / (_)                       7/          #\n"
           "        | |/ |/ /  __/ / /__/ /_/ / / / / / /  __/  / /___/ / _                        с0?           #\n"
           "        |__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/  /_____/_/ (_)                   _,^N'             #\n"
           "                                                                              _,.;^                  #\n"
           "                                                                          ,y;^                       #\n"
           "                                                                     ,'^0'                           #\n"
    );
}

void getLocation() {
    char location[SIZE_BUFF];
    char *username = getlogin();

    if (username == NULL) {
        username = getenv("USER"); 
        if (username == NULL) {
            username = getenv("LOGNAME"); 
            if (username == NULL) {
                printf("Error getting username\n");
                return;
            }
        }
    }
    if (getcwd(location, SIZE_BUFF) == NULL){
        printf("Error\n");
    }
    else {
        printf("\033[1;32m%s@LT-MSI\033[1;34m:%s\033[0m:$ ", username, location);
    }
}

void logout(char *input)
{
    char *lowercase_input = strdup(input);
    for (int i = 0; lowercase_input[i]; i++) {
        lowercase_input[i] = tolower(lowercase_input[i]);
    }

    if (strstr(lowercase_input, "exit") != NULL) {
        free(input);
        free(lowercase_input);
        puts("logout");
        exit(EXIT_SUCCESS); 
    } else {
        free(input);
        free(lowercase_input);
    }
}


char *getInputFromUser()
{
    char *str = (char *)malloc(sizeof(char));
    int index = 0;
    char ch;
    while ((ch = getchar()) != '\n')
    {
        str[index] = ch;
        index++;
        str = (char *)realloc(str, (index + 1) * sizeof(char));
        if (str == NULL) {
            free(str);
            return NULL;
        }
    }

    str[index] = '\0';

    return str;
}

char *my_strtok(char *str, const char delim,int check_quotes) {
    static char *next_token = NULL; 
    char *token;
    static int check_quotes_saved;

    if (str != NULL) { 
        token = str; 
        next_token= NULL;
        check_quotes_saved = check_quotes;
    } 
    else {
    
        if (next_token == NULL) { 
            return NULL;
        }
        token = next_token;
    }
    if(check_quotes_saved) {
        if(*token == '"') {
            token++;
            char *end = strchr(token, '"');
            if(end != NULL) {
                next_token = end;
                *next_token = '\0';
                next_token++;
            if(*next_token=='\0'){
            next_token=NULL;
            }
            else{
            next_token++;
            }
            return token;
            }
            token--;
        }
    }
    int size = strlen(token);
     if(*(token)==delim){
    for(int i=0; i<size;i++){
       if(*(token+i)!= delim){
              token=token+i;
              break;
           }
        }
    }
    
    for(int i=0;i<strlen(token);i++){ 

        if(*(token+i)== delim && *(token+i+1)!= delim){
            next_token=token+i;
            break;
        }
        if(i==strlen(token)-1){
            next_token=NULL;
        }
    }
    if (next_token != NULL) {
        *next_token = '\0';
        next_token ++;
    }
    return token;
}
char **splitArgument(char *str){
    char *subStr;
    subStr = my_strtok(str, ' ',1);
    int size = 2;
    int index = 0;
    char **argumnts = (char **)malloc(size * sizeof(char *));
    *(argumnts + index) = subStr;
    while ((subStr = my_strtok(NULL, ' ',1)) != NULL)
    {
        index++;
        size++;
        argumnts = (char **)realloc(argumnts, size * sizeof(char *));
        *(argumnts + index) = subStr;
    }
    *(argumnts + (index + 1)) = NULL;

    return argumnts;
}
char* concatenateStrings(char** arguments,int size){
    char *temp = (char *)malloc((strlen(arguments[1]) + 1) * sizeof(char));
        strcpy(temp, arguments[1]); 
        memmove(temp,temp+1,strlen(temp));
        strcat(temp, " "); 
        for(int j=2;j<size;j++){
            temp = (char *)realloc(temp,((strlen(arguments[j])+2) * sizeof(char)));
            if(j == size-1){
                strcat(temp, arguments[j]); 
                 temp[strlen(temp)-1] = '\0';
            }
            else{
               strcat(temp, arguments[j]); 
                 strcat(temp, " "); 
            }  
        }
    return temp;
}

void cd(char **path) {
    if (path[2] != NULL) {
        printf("-myShell: cd: too many arguments\n");
        return;
    }
     if (chdir(path[1]) != 0)  
        printf("-myShell: cd: %s: No such file or directory\n", path[1]);
}

void cp(char **arguments)
{
    char ch;
    FILE *src, *des;
    if ((src = fopen(arguments[1], "r")) == NULL){
        puts("error");
        return;
    }

    if ((des = fopen(arguments[2], "w")) == NULL){
        puts("error");
        fclose(src);
        return;
    }
    while ((ch = fgetc(src)) != EOF){
        fputc(ch, des);
    }
    fclose(src);
    fclose(des);
}

void echo(char **arguments){
    while (*(++arguments))
        printf("%s ", *arguments);
    puts("");
}

void delete(char **path)
{
    if (path[1] == NULL){
        printf("-myShell: delete: Missing file name\n");
        return;
    }

    char *resolved_path = realpath(path[1], NULL);
    if (resolved_path == NULL){
        perror("-myShell: delete");
        printf("-myShell: delete: %s: No such file or directory\n", path[1]);
    }
    else{
        if (unlink(resolved_path) != 0){
            perror("-myShell: delete");
            printf("-myShell: delete: %s: No such file or directory\n", resolved_path);
        }

        free(resolved_path);
    }
}

void mypipe(char **argv1, char **argv2){
    int fildes[2];
    if (fork() == 0){
        pipe(fildes);
        if (fork() == 0){
            close(STDOUT_FILENO);
            dup(fildes[1]);
            close(fildes[1]);
            close(fildes[0]);
            execvp(argv1[0], argv1);
        }
        close(STDIN_FILENO);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
        execvp(argv2[0], argv2);
    }
}

void splitInputForPipe(char *input, char ***argv1, char ***argv2){
    char *pipePos = strchr(input, '|');
    if (!pipePos)
        return; 

    int firstCommandLength = pipePos - input;
    char firstCommand[firstCommandLength + 1];
    strncpy(firstCommand, input, firstCommandLength);
    firstCommand[firstCommandLength] = '\0';

    char *secondCommand = pipePos + 1; 

    int argc1 = 0;
    char **args1 = malloc(sizeof(char *));
    char *token = my_strtok(firstCommand, ' ', 1);
    while (token)
    {
        args1 = realloc(args1, sizeof(char *) * (argc1 + 1));
        args1[argc1++] = strdup(token);
        token = my_strtok(NULL, ' ', 1);
    }
    args1 = realloc(args1, sizeof(char *) * (argc1 + 1)); 
    args1[argc1] = NULL;                                 

    int argc2 = 0;
    char **args2 = malloc(sizeof(char *));
    token = my_strtok(secondCommand, ' ', 1);
    while (token)
    {
        args2 = realloc(args2, sizeof(char *) * (argc2 + 1));
        args2[argc2++] = strdup(token);
        token = my_strtok(NULL, ' ', 1);
    }
    args2 = realloc(args2, sizeof(char *) * (argc2 + 1));
    args2[argc2] = NULL;                                  

    *argv1 = args1;
    *argv2 = args2;
}

void move(char **args){
    if (args == NULL || args[1] == NULL || args[2] == NULL){
        printf("Usage: move <source> <destination>\n");
        return;
    }
    char *sourcePath = realpath(args[1], NULL); 
    if (sourcePath == NULL){
        perror("Error: Failed to resolve source path");
        return;
    }

    char destPath[PATH_MAX];
    if (realpath(args[2], destPath) == NULL){
        perror("Error: Failed to resolve destination path");
        free(sourcePath);
        return;
    }

    struct stat destStat;
    if (stat(destPath, &destStat) == 0 && S_ISDIR(destStat.st_mode)){
        char *sourceFileName = basename(sourcePath);
        if (strlen(destPath) + strlen(sourceFileName) + 2 > PATH_MAX){
            printf("Error: Destination path is too long\n");
            free(sourcePath);
            return;
        }
        strcat(destPath, "/");
        strcat(destPath, sourceFileName);
    }
    if (rename(sourcePath, destPath) != 0){
        perror("Error: Failed to move the file");
    }
    else{
        printf("File moved successfully from '%s' to '%s'\n", sourcePath, destPath);
    }
    free(sourcePath);
}
void echoppend(char **arguments)
{
    int size=0;
     while (arguments[size] != NULL) {
        size++;
    }
    FILE *file;
    
    if ((file = fopen(arguments[size-1], "a")) == NULL)
    {
        puts("error");
        return;
    }
   for (int i = 1; i < size-2; i++){
    fprintf(file, "%s ", arguments[i]);
   }
    fprintf(file, "%s ","\n");
    fclose(file);
}
void echorite(char **arguments)
{
    int size=0;
     while (arguments[size] != NULL) {
        size++;
    }
    FILE *file;
    
    if ((file = fopen(arguments[size-1], "w")) == NULL)
    {
        puts("error");
        return;
    }
   for (int i = 1; i < size-2; i++){
    fprintf(file, "%s ", arguments[i]);
   }
    fprintf(file, "%s ","\n");
    fclose(file);
}
void readfile(char **arguments)
{
    if(arguments[1]==NULL){
        puts("error");
        return;
    }
    if(arguments[2]!=NULL){
        puts("error");
        return;
    }
    FILE *file;
    char ch;
    if ((file = fopen(arguments[1], "r")) == NULL)// פתיחת הקובץ
    {
        puts("error");
        return;
    }
    while ((ch = fgetc(file)) != EOF)// קריאת הקובץ
        putchar(ch);
    fclose(file);
}
void wordCount(char **arguments){
    if(arguments[1]==NULL||arguments[2]==NULL){
        puts("error");
        return;
    }
    if(arguments[3]!=NULL){
        puts("error");
        return;
    }
    FILE *file;
    char ch;
    int wordCount = 0, lineCount = 0;
    char prevChar = '\0';
    int inWord = 0;
    if ((file = fopen(arguments[2], "r")) == NULL){
        puts("error");
        return;
    }
    while ((ch = fgetc(file)) != EOF)
    {
        if ((ch == ' ' || ch == '\n' || ch == '\t') && !inWord){
            inWord = 1;
            wordCount++;
          if (ch == '\n') {
            lineCount++;
            }
        } 
        else if (ch != ' ' && ch != '\n' && ch != '\t') {
            inWord = 0;
        }
    }
     prevChar = ch;
    if (prevChar != ' ' && prevChar != '\n' && prevChar != '\t') {
        wordCount++;
    }
    fclose(file);
    if (strcmp(arguments[1], "-l") == 0){
        printf("%d %s\n", lineCount, arguments[2]);
    }
     else if (strcmp(arguments[1], "-w") == 0){
        printf("%d %s\n", wordCount, arguments[2]);
     }
     else printf("wc: invalid option -- '%c'\n", arguments[1][1]);
}