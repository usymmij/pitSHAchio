Client: Client.o socket.o
	g++ -o Client Client.o socket.o -pthread -l rt

Client.o : Client.cpp socket.h
	g++ -c Client.cpp 

thread.o : thread.cpp thread.h ThreadSem.h
	g++ -c thread.cpp

socket.o : socket.cpp socket.h
	g++ -c socket.cpp

Cleaner : CleanThreadSem.cpp
	g++ -o Cleaner CleanThreadSem.cpp -pthread -l rt

