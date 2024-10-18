prefix=/usr/local
CC = g++

CFLAGS = -Wall -std=c++11 -lpthread
SRC = carrera.cpp
OBJ = carrera.o
APP = carrera

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(APP) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJ) $(APP)

install: $(APP)
	install -m 0755 $(APP) $(prefix)/bin

uninstall: $(APP)
	$(RM) $(prefix)/bin/$(APP)