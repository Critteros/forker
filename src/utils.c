#include "pch.h"
#include "utils.h"
#include "globals.h"

#define BUFFER_SIZE 65536

void utils_clearFifoFiles(void)
{
    const char *targetDirectory = ".";
    DIR *dp = opendir(targetDirectory);
    if (dp != NULL)
    {
        struct dirent *ep = NULL;
        while ((ep = readdir(dp)))
        {
            if (ep->d_type == DT_FIFO)
            {
                LOG(YELLOW("Clearing file: %s\n"), ep->d_name);
                remove(ep->d_name);
            }
        }

        closedir(dp);
    }
    else
    {
        switch (errno)
        {
        case EACCES:
            fprintf(stderr, "Failed to open the directory [%s] PERMISSION DENIED\n", targetDirectory);
            break;

        default:
            fprintf(stderr, "Could not open the directory [%s]\n", targetDirectory);
        }
    }
}

char *utils_execProgram(const char *filepath)
{
    FILE *fs = popen(filepath, "r");
    if (fs == NULL)
    {
        return NULL;
    }
    char buffer[BUFFER_SIZE] = {0};
    size_t readSize = 0;
    size_t outputSize = 0;
    char *out = NULL;
    while ((readSize = fread(buffer, sizeof(char), BUFFER_SIZE, fs)))
    {

        out = realloc(out, outputSize + readSize);
        memcpy(out + outputSize, buffer, readSize);
        outputSize += readSize;
    }

    out[outputSize - 1] = '\0';

    pclose(fs);

    return out;
}

void utils_replaceChar(char *input, const char whatChar, const char toChar)
{
    for (char *i = input; *i != '\0'; i++)
    {
        *i = *i == whatChar ? toChar : *i;
    }
}

void utils_cloneProcess(childMain_t mainF)
{
    //Ids for children
    ++childID;
    switch (fork())
    {
    //Case ERROR
    case -1:
        fprintf(stderr, "Could not fork exitting!\n");
        exit(EXIT_FAILURE);
        break;
    //Case in child
    case 0:
        mainF();
        exit(EXIT_SUCCESS);
        break;
    //Case in parent
    default:
        return;
        break;
    }
}

int utils_dirExists(const char *path)
{
    DIR *dir = opendir(path);
    if (dir)
    {
        closedir(dir);
        return 1;
    }

    if (errno == ENOENT)
    {
        return 0;
    }

    return 0;
}