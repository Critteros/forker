#include "protocol.h"

static size_t headerSize = sizeof(struct packetHeader);

int sendPacket(int fd,
               byte_t *data,
               size_t dataSize,
               packetType_t packetType,
               dataType_t dataType)
{
    const size_t packetSize = headerSize + dataSize;
    PACKET packet = calloc(1, packetSize);

    //Filling the header
    packet->header.senderPid = getpid();
    packet->header.packetType = packetType;
    packet->header.dataType = dataType;
    packet->header.dataSize = dataSize;
    packet->header.packetSize = packetSize;

    //Filling data
    memcpy(packet->data, data, dataSize);

    //Packet is now ready to be send
    ssize_t writeAmount = write(fd, packet, packetSize);
    //Error has occured
    if (writeAmount == -1)
    {
        free(packet);
        return 0;
    }
    //Prevent partial write
    assert((writeAmount == (ssize_t)packetSize));

    free(packet);
    return 1;
}

PACKET receivePacket(int fd)
{
    struct packetHeader header = {0};

    //Read header part of packet
    ssize_t readAmount = -1;
    while (1)
    {
        readAmount = read(fd, &header, headerSize);
        if (readAmount > 0)
            break;
        else if (readAmount == -1)
        {
            //Error has occured
            fprintf(stderr, "Error: %s has occured when recieving packet header exitting!", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    //Prevent partial reads
    assert(readAmount == (ssize_t)headerSize);

    //Now we can recieve full packet
    const size_t dataSize = header.dataSize;
    const size_t packetSize = header.packetSize;
    assert((dataSize + headerSize) == packetSize);

    PACKET packet = calloc(1, packetSize);
    memcpy(&packet->header, &header, headerSize);

    //Reading data segment
    readAmount = -1;
    while (1)
    {
        readAmount = read(fd, packet->data, dataSize);
        if (readAmount > 0)
            break;
        else if (readAmount == -1)
        {
            //Error has occured
            fprintf(stderr, "Error: %s has occured when recieving packet data exitting!", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    assert(readAmount == (ssize_t)dataSize);

    return packet;
}