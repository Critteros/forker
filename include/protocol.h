#pragma once

#include "pch.h"
#include "globals.h"
#include "stdint.h"
#include "assert.h"

typedef enum
{
    PACKET_HELLO,
    PACKET_DATA,
    PACKET_TERMINATE
} packetType_t;

typedef enum
{
    DATA_INT,
    DATA_UINT,
    DATA_STRING,
    DATA_BYTES
} dataType_t;

typedef uint8_t byte_t;
struct packetHeader
{
    pid_t senderPid;
    packetType_t packetType;
    dataType_t dataType;
    size_t dataSize;
    size_t packetSize;
};

typedef struct packet
{
    struct packetHeader header;
    byte_t data[];
} * PACKET;

/**
 * @brief Send a single packet over open file descriptor
 * 
 * @param fd opened file descriptor to a propably fifo queque
 * @param data array of data to send in bytes
 * @param dataSize size of data to send
 * @param packetType type of packet to send 
 * @param dataType type of data that we are sending
 * @return int 1 if packet was send and 0 on error
 */
int sendPacket(int fd,
               byte_t *data,
               size_t dataSize,
               packetType_t packetType,
               dataType_t dataType);

/**
 * @brief Recieves a single packet over open file descriptor
 * @warning The caller must free PACKET memory
 * 
 * @param fd opened file descriptor to a propably fifo queque
 * @return PACKET recived packet
 */
PACKET receivePacket(int fd);

static_assert(
    (sizeof(struct packet) == sizeof(struct packetHeader)),
    "Header and Structs have invalid size");