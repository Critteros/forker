#include "pch.h"
#include "client.h"
#include "globals.h"
#include "protocol.h"

void childMain(void)
{
    pid_t pid = getpid();
    LOG(GREEN("->Created child ID=%d pid=%d\n"), childID, pid);

    //Opening server fifo for write
    int serverFifo = open(serverFifoPath, O_WRONLY);
    char oursFifo[256] = {0};
    const char *format = fifos_DIR "fifo_%d";
    sprintf(oursFifo, format, pid);
    sendPacket(
        serverFifo,
        (byte_t *)oursFifo,
        strlen(oursFifo) + 1,
        PACKET_HELLO,
        DATA_STRING);

    LOG(RED("X Exitting child ID=%d pid=%d\n"), childID, pid);
}