#include "pch.h"
#include "client.h"
#include "globals.h"
#include "protocol.h"
#include "server.h"

void childMain()
{

    pid_t pid = getpid();
    char oursFifo[256] = {0};
    const char *format = "fifo_%d";
    sprintf(oursFifo, format, pid);
    mkfifo(oursFifo, S_IRUSR | S_IWUSR);

    LOG(GREEN("->Created child ID=%d pid=%d\n"), childID, pid);

    //Opening server fifo for write
    int serverFifo = open(serverFifoName, O_WRONLY);

    sendPacket(
        serverFifo,
        (byte_t *)oursFifo,
        strlen(oursFifo) + 1,
        PACKET_HELLO,
        DATA_STRING);

    //Waiting to recieve ls data from server
    int fd = open(oursFifo, O_RDONLY);
    PACKET packet = receivePacket(fd);
    assert(packet->header.packetType == PACKET_DATA);
    assert(packet->header.dataType == DATA_BYTES);

    size_t dataSize = packet->header.dataSize;
    struct message *msg = calloc(1, dataSize);
    memcpy(msg, packet->data, dataSize);
    free(packet);

    char *message = (char *)msg->bytes;
    int id = msg->id;

    LOG(YELLOW("Recived message in child (%d): %s\n"), pid, message);

    printf("Klient %d (%d): %s\n", id, pid, message);

    free(msg);
    LOG(RED("X Exitting child ID=%d pid=%d\n"), childID, pid);
}