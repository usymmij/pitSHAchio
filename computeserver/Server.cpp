#include "thread.h"
#include "socketserver.h"
#include <stdlib.h>
#include <time.h>
#include <list>
#include <vector>

using namespace Sync;

class socketThread : public Thread
{
private:
    // create a socket
    Socket &sock;
    bool &end;
    ByteArray &bArr;
    std::vector<socketThread *> &threadsList;

public:
    // constructor
    socketThread(Socket &s, bool &end, std::vector<socketThread *> &clientSocketThread) : sock(s), end(end), threadsList(clientSocketThread) {}

    ~socketThread()
    {
        // clean up
        this->terminationEvent.Wait();
    }

    // get socket
    Socket &getSocket()
    {
        return sock;
    }

    virtual long ThreadMain()
    {
        try
        {
            while (!end)
            {
                // read from the socket
                sock.Read(bArr);

                // convert message to string
                std::string message = bArr.ToString();

                // do whatever haven't decided yet
            }
        }
        catch (std::string &s)
        {

            std::cout << s << std::endl;
        }
        catch (std::string error)
        {
            std::cout << error << std::endl;
        } // try catch

        std::cout << "Client disconnected" << std::endl;

        return 0;
    }
};

class serverThread : public Thread
{
private:
    SocketServer &server;
    std::vector<socketThread *> &threadsList;
    bool end = false;

public:
    serverThread(SocketServer &server)
        : server(server) {}

    ~serverThread()
    {

        for (auto t : sockThreadList)
        {
            try
            {
                // close the socket
                Socket &s = t->getSocket();

                s.close();
            }
            catch (...)
            {

                std::cout << "Error closing socket" << std::endl;
            }
        }

        // clear the list
        std::vector<socketThread *>().swap(sockThreadList);

        // clean up
        std::cout << "Server thread terminated" << std::endl;

        end = true;
    }

    virtual long ThreadMain()
    {
        while (1)
        {
            try
            {

                Socket *newConnection = new Socket(server.accept());

                Socket &socketRef = *newConnection;

                socketThreadList.push_back(new socketThread(socketRef, end, socketThreadList));
            }
            catch (std::string error)
            {

                std::cout << error << std::endl;

                return 1;
            }
            catch (TerminationException t)
            {
                std::cout << "Server thread terminated" << std::endl;

                return t;
            }
        }
        return 0;
    }
};

int main(void)
{
    std::cout << "I am a server." << std::endl;

    std::cout << "Press something to close the server ";

    std::cout.flush();

    // create a new socket server
    SocketServer server(3000);
    ServerThread serverThread(server);

    // start the server thread
    FlexWait cinWaiter(1, stdin);

    cinWaiter.Wait();
    std::cin.get();

    server.Shutdown();
    // shutdown the server
}
