#include "main.hpp"

/*
    Functie care verifica daca un fisier exista.
*/
bool fileExists(char *filename)
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

/*
    Functie care verifica daca argumentele sunt corecte.
*/
void checkArguments(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Numar incorect de argumente.\n");
        exit(1);
    }

    int numberOfMappers = atoi(argv[1]);
    int numberOfReducers = atoi(argv[2]);

    if (numberOfMappers < 1)
    {
        printf("Numar incorect de mappers.\n");
        exit(EXIT_FAILURE);
    }

    if (numberOfReducers < 1)
    {
        printf("Numar incorect de mappers.\n");
        exit(EXIT_FAILURE);
    }

    if (!fileExists(argv[3]))
    {
        printf("Fisierul %s nu exista.\n", argv[3]);
        exit(EXIT_FAILURE);
    }
}

/**
 * Functie care returneaza dimensiunea unui fisier.
 */
size_t findSize(char *fileName)
{
    FILE *filePointer = fopen(fileName, "r");
    printf("Fisierul este %s", fileName);
    if (filePointer == NULL)
    {
        printf("File Not Found!\n");
        exit(EXIT_FAILURE);
    }

    fseek(filePointer, 0L, SEEK_END);
    size_t res = ftell(filePointer);
    fclose(filePointer);

    return res;
}

/*
 */
bool checkExistenceNewLine(char *buffer)
{
    return buffer[strlen(buffer) - 1] == '\n';
}

/*
 */
std::map<std::string, ssize_t> processFile(char *fileName, ssize_t counter)
{
    std::fstream file;
    std::map<std::string, ssize_t> map;
    std::string word;

    file.open(fileName);
    while (file >> word)
    {
        for (auto &x : word)
        {
            x = tolower(x);
        }
        word = removeSpecialCharacter(word);
        if (map.find(word) == map.end())
        {
            map[word] = counter;
        }
    }

    file.close();
    return map;
}

/*
*/
std::string removeSpecialCharacter(std::string input)
{
    std::string output = "";
    for (std::size_t i = 0; i < input.size(); i++)
    {
        bool isAlphanumeric = (input[i] >= 'a' && input[i] <= 'z') || 
                              (input[i] >= 'A' && input[i] <= 'Z') ||
                              (input[i] >= '0' && input[i] <= '9');
        if (isAlphanumeric) {
            output += input[i];
        }
    }
    return output;
}

/*
    Functie care citeste continutul unui fisier, procensandu-l.
*/
std::map<std::string, std::vector<ssize_t>> processInputFiles(char *inputFileName)
{

    FILE *filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen(inputFileName, "r");
    ssize_t counter = 1;
    std::map<std::string, std::vector<ssize_t>> finalMap;

    while (fgets(buffer, bufferLength, filePointer))
    {
        int resultParsingInt = atoi(buffer);

        if (resultParsingInt == 0)
        {
            if (checkExistenceNewLine(buffer))
            {
                buffer[strlen(buffer) - 1] = '\0';
            }
            size_t size = findSize(buffer);
            std::map<std::string, ssize_t> map = processFile(buffer, counter);
            counter++;
            for (auto word : map)
            {
                if (finalMap.find(word.first) == finalMap.end())
                {
                    finalMap[word.first] = std::vector<ssize_t>();
                }
                int value = count(finalMap[word.first].begin(), finalMap[word.first].end(), word.second);
                if (value == 0)
                {
                    finalMap[word.first].push_back(word.second);
                }
            }
            printf("Dimensiunea fisierului %s este %ld bytes\n", buffer, size);
        }
    }

    fclose(filePointer);
    return finalMap;
}

int main(int argc, char **argv)
{
    checkArguments(argc, argv);

    int numberOfMappers = atoi(argv[1]);
    int numberOfReducers = atoi(argv[2]);

    printf("Numarul de mappers este %d\n", numberOfMappers);
    printf("Numarul de reducers este %d\n", numberOfReducers);

    char *inputFileName = argv[3];
    std::map<std::string, std::vector<ssize_t>> finalMap;
    finalMap = processInputFiles(inputFileName);
    for (auto word : finalMap)
    {
        printf("%s:[", word.first.c_str());
        for (auto position : word.second)
        {
            if (position == word.second.back())
            {
                printf("%ld", position);
                break;
            }
            printf("%ld ", position);
        }
        printf("]\n");
    }
    return 0;
}