CC=gcc
LINK=gcc
CFLAGS=-c -Wall -I.
OBJECT_FILES= Sensor.o Driver.o Server.o gpioDIO.o
LIBS = -lpthread

.SUFFIXES: .c .o

.c .o:
	$(CC) $(CFLAGS) -o $@ $< 

Server: $(OBJECT_FILES)
	$(LINK) $(OBJECT_FILES) $(LIBS) -o $@

Server.o: Server.c
gpioDIO.o: gpioDIO.c
Sensor.o: Sensor.c
Driver.o: Driver.c