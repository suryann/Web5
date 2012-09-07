CC=g++
CFLAGS=-c -Wall
LDFLAGS= -lmysqlclient -lpthread 
SOURCES= main.cpp ./common/types.h ./common/DatabaseClass.cpp ./common/DatabaseClass.h ./common/SocketClass.h ./common/SocketClass.cpp ./common/ListenerClass.cpp ./common/ListenerClass.h ./common/ThreadClass.cpp ./common/ThreadClass.h ./common/PacketClass.cpp ./common/PacketClass.h ./common/Parser.cpp ./common/Parser.h ./common/PacketBuffer.cpp ./common/PacketBuffer.h ./common/SemaphoreClass.cpp ./common/SemaphoreClass.h ./common/LockClass.cpp ./common/LockClass.h ./common/hash/md5.cpp ./common/hash/md5.h ./common/json/jsonxx.cc ./common/json/jsonxx.h ./common/Logger.cpp ./common/Logger.h ./common/Player.h ./common/Player.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE= WSServer

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

