#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>

bool file_exists (char *filename) {
    struct stat buffer;   
    return (stat (filename, &buffer) == 0);
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("Numar incorect de argumente\n");
        exit(1);
    }
    
    int numberOfMappers = atoi(argv[1]);
    int numberOfReducers = atoi(argv[2]);

    if (numberOfMappers < 1) {
        printf("Numar incorect de mappers sau reducers\n");
        exit(1);
    }

    if (numberOfReducers < 1) {
        printf("Numar incorect de mappers sau reducers\n");
        exit(1);
    }

    if (!file_exists(argv[3])) {
        printf("Fisierul %s nu exista\n", argv[3]);
        exit(1);
    }
    return 0;
}