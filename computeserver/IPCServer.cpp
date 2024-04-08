#include "socket.h"
#include "socketserver.h"
#include "Blockable.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>

void run_IPC(Sync::ByteArray *hex, Sync::ThreadSem sem, Sync::SocketServer main)
{
    Sync::SocketServer server(3030);
    Sync::ByteArray in;

    for (;;)
    {
        Sync::Socket socket = server.Accept();
        int err = socket.Read(in);
        sem.Wait();
        *hex = Sync::ByteArray(in.ToString());
        sem.Signal();
        if (in.ToString()[0] == 't')
        {
            std::cout << "terminating server" << std::endl;
            socket.Close();
            main.Shutdown();
            return;
        }
        std::cout << "new hash received: ";
        std::cout << in.ToString() << std::endl;
    }
}