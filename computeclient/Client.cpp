#include <iostream>
#include <string>
#include "socket.h"

int main(void)
{
    try
    {
        Socket theSocket("127.0.0.1", 2000);
        theSocket.Open();
        std::string message = "";

        while (message != "done")
        {
            std::cout << "Enter a message to send (type 'done' to exit): ";
            std::getline(std::cin, message);

            ByteArray ba(message);
            int written = theSocket.Write(ba);

            if (written != ba.v.size())
            {
                std::cout << "The socket appears to have been closed" << std::endl;
                break;
            }
            else
            {
                std::cout << "Sent: " << message << std::endl;
            }

            if (theSocket.Read(ba) <= 0)
            {
                std::cout << "The socket appears to have been closed" << std::endl;
                break;
            }

            std::cout << "Received: " << ba.ToString() << std::endl;
        }

        std::cout << "Exiting client program." << std::endl;
        theSocket.Close();
    }
    catch (std::string s)
    {
        std::cout << s << std::endl;
    }
    catch (...)
    {
        std::cout << "Caught unexpected exception" << std::endl;
    }

    return 0;
}
