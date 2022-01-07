#pragma once
#include <stdio.h>

//For concatenating two strings
#define concat(a, b) a##b

#ifdef DEBUG_LOG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

#ifndef SERVER_FIFO
#define serverFifoName "fifo_server"
#else
#define serverFifoName SERVER_FIFO
#endif

#ifdef GLOBAL_IMPLEMENTATION
#define GLOBAL
#else
#define GLOBAL extern
#endif

#define fifos_DIR "fifos/"
#define serverFifoPath (fifos_DIR serverFifoName)

//Colors
#define RED(x) "\033[31m" x "\033[0m"
#define GREEN(x) "\033[32m" x "\033[0m"
#define MAGENTA(x) "\033[35m" x "\033[0m"
#define YELLOW(x) "\033[33m" x "\033[0m"

GLOBAL int numberOfClient;
GLOBAL int childID;
