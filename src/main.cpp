#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>

/*
    Functie care verifica daca un fisier exista.
*/
bool fileExists (char *filename) {
    struct stat buffer;   
    return (stat (filename, &buffer) == 0);
}

/*
    Functie care verifica daca argumentele sunt corecte.
*/
void checkArguments(int argc, char **argv) {
    if (argc != 4) {
        printf("Numar incorect de argumente.\n");
        exit(1);
    }
    
    int numberOfMappers = atoi(argv[1]);
    int numberOfReducers = atoi(argv[2]);

    if (numberOfMappers < 1) {
        printf("Numar incorect de mappers.\n");
        exit(EXIT_FAILURE);
    }

    if (numberOfReducers < 1) {
        printf("Numar incorect de mappers.\n");
        exit(EXIT_FAILURE);
    }

    if (!fileExists(argv[3])) {
        printf("Fisierul %s nu exista.\n", argv[3]);
        exit(EXIT_FAILURE);
    }
}

/**
 * Functie care returneaza dimensiunea unui fisier.
 */
size_t findSize(char *fileName) 
{ 
    FILE* filePointer = fopen(fileName, "r"); 
   
    if (filePointer == NULL) { 
        printf("File Not Found!\n"); 
        exit(EXIT_FAILURE); 
    } 
  
    fseek(filePointer, 0L, SEEK_END); 
    size_t res = ftell(filePointer);  
    fclose(filePointer); 
  
    return res; 
}

/*
    Functie care citeste continutul unui fisier, procensandu-l.
*/
void processInputFiles(char *inputFileName) {
   
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen(inputFileName, "r");

    while(fgets(buffer, bufferLength, filePointer)) {
        int resultParsingInt = atoi(buffer);
        if(resultParsingInt == 0) {
            size_t size = findSize(buffer);
            printf("Dimensiunea fisierului %s este %ld bytes\n", buffer, size);
        }
    }

    fclose(filePointer);
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    checkArguments(argc, argv);
    
    int numberOfMappers = atoi(argv[1]);
    int numberOfReducers = atoi(argv[2]);

    printf("Numarul de mappers este %d\n", numberOfMappers);
    printf("Numarul de reducers este %d\n", numberOfReducers);

    char *inputFileName = argv[3];
    processInputFiles(inputFileName);
    return 0;
}