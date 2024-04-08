#include "socket.h"
#include "socketserver.h"
#include "IPCServer.h"
#include "Blockable.h"
#include <iostream>
#include <unistd.h>
#include <thread>

bool shutdown_f = false;
int clientCount = 0;

int socketReply(Sync::Socket s)
{
    Sync::ByteArray message;

    clientCount += 1;

    int ret = s.Read(message);
    std::string reply = message.ToString();
    reply = reply.erase(0, 1);
    Sync::ByteArray re(reply);
    s.Write(re);
    return 0;
}

void mainServer(Sync::ByteArray *hash, Sync::ThreadSem sem, Sync::SocketServer server)
{
    try
    {
        for (;;)
        {
            Sync::Socket s = server.Accept();
            std::thread th(socketReply, s);
            th.detach();
        }
    }
    catch (int e)
    {
        std::cout << e << std::endl;
    }
}

int main()
{
    Sync::SocketServer server(3060);
    Sync::ByteArray hash;

    Sync::ThreadSem sem(1);

    std::thread ipcServer_thread(run_IPC, &hash, sem, server);

    std::thread mainServer_thread(mainServer, &hash, sem, server);

    ipcServer_thread.join();
    mainServer_thread.join();
}