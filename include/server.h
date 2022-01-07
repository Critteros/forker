#pragma once
#include "protocol.h"

void serverMain(void);

struct message
{
    int id;
    byte_t bytes[];
};