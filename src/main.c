#include "pch.h"
#include "utils.h"
#include "client.h"
#include "server.h"

#define GLOBAL_IMPLEMENTATION
#include "globals.h"

int main(int argc, char *argv[])
{
    //Print usage information
    if (argc < 2)
    {
        printf("Usage: %s (num of clients)\n", argv[0]);
        return 0;
    }
    pid_t pid = getpid();
    LOG(MAGENTA("Parent pid=%d\n\n"), pid);

    //Evaluating passed argument
    int val = atoi(argv[1]);
    if (val < 0)
    {
        fprintf(stderr, "Invalid client amount (%d) the value must be a positive integer\n", val);
    }

    //Global initialisation
    numberOfClient = val;

    //Checking if dir exists
    if (!utils_dirExists(fifos_DIR))
    {
        int status = mkdir(fifos_DIR, S_IRWXU);
        if (status == -1)
        {
            fprintf(stderr, "error: [%s] occured while making a directory, exitting\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }

    //Clar any remaining fifo files before proceeding
    utils_clearFifoFiles(fifos_DIR);

    //Create server fifo queque
    mkfifo(serverFifoPath, S_IRUSR | S_IWUSR);

    for (int i = 0; i < numberOfClient; i++)
    {
        utils_cloneProcess(childMain);
    }

    serverMain();

    //Wait for all childs
    while (wait(NULL) >= 0)
    {
    }

    LOG(MAGENTA("\nExitting Main (%d)\n"), pid);
    return EXIT_SUCCESS;
}