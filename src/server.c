#include "pch.h"
#include "server.h"
#include "stringVector.h"
#include "globals.h"
#include "protocol.h"

void serverMain(void)
{
    //Open server fifo file for reading
    int serverFifo = open(serverFifoPath, O_RDONLY);

    //Read hello packtes
    for (int i = 0; i < numberOfClient; i++)
    {
        PACKET packet = receivePacket(serverFifo);
        assert(packet->header.packetType == PACKET_HELLO);
        assert(packet->header.dataType == DATA_STRING);

        const char *message = (const char *)packet->data;
        LOG(YELLOW("Recived hello nr [%d/%d]: %s\n"), i + 1, numberOfClient, message);
        free(packet);
    }

    close(serverFifo);
}