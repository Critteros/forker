#include "pch.h"
#include "server.h"
#include "stringVector.h"
#include "globals.h"
#include "protocol.h"
#include "utils.h"

void serverMain(void)
{
    //Open server fifo file for reading
    int serverFifo = open(serverFifoName, O_RDONLY);

    char **childDescriptorNames = calloc((size_t)numberOfClient, sizeof(char *));

    //Read hello packtes
    for (int i = 0; i < numberOfClient; i++)
    {
        PACKET packet = receivePacket(serverFifo);
        assert(packet->header.packetType == PACKET_HELLO);
        assert(packet->header.dataType == DATA_STRING);

        const char *message = (const char *)packet->data;
        LOG(YELLOW("Recived hello nr [%d/%d]: %s\n"), i + 1, numberOfClient, message);

        childDescriptorNames[i] = calloc(strlen(message) + 1, sizeof(char));
        strcpy(childDescriptorNames[i], message);

        free(packet);
    }

    //Now get ls data and send that to each client

    //For each child
    for (int i = 0; i < numberOfClient; i++)
    {
        size_t lsOutputSize = strlen(lsOutputs[i]) + 1;
        size_t structSize = sizeof(struct message) + lsOutputSize;
        struct message *msg = calloc(1, structSize);
        msg->id = i + 1;
        memcpy(msg->bytes, lsOutputs[i], lsOutputSize);

        int fd = open(childDescriptorNames[i], O_WRONLY);
        sendPacket(fd,
                   (byte_t *)msg,
                   structSize,
                   PACKET_DATA,
                   DATA_BYTES);

        free(msg);
        close(fd);
    }

    //Cleanup
    for (int i = 0; i < numberOfClient; i++)
    {
        free(childDescriptorNames[i]);
    }
    free(childDescriptorNames);

    close(serverFifo);
}