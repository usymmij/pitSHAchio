#ifndef IPCSERVER_H
#define IPCSERVER_H
#include "socket.h"
#include "Blockable.h"

void run_IPC(Sync::ByteArray* hex, Sync::ThreadSem sem, Sync::SocketServer main);

#endif