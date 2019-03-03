#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include "gpioDIO.h"
#include "gpioIOCounter.h"
#include "pthread.h"
#include "Sensor.h"
#include "Surucu.h"

//Connection fd's
#define MAX_CON 1
int con[MAX_CON];
int conSize = 0;
int server_fd;
struct sockaddr_in caddr, saddr;

int doneReading = 0;
Sensor sensorler[2];
Surucu* relay;

void readSensorValues(int);

void *makeConnection(void *arg) {

	while (conSize < MAX_CON) {
		//Accept connection request and connect
		socklen_t addrSize = sizeof(caddr);
		if ((con[conSize] = accept(server_fd, (struct sockaddr*)&caddr, &addrSize)) == -1) {
			printf("Error socket accept [%s] \n", strerror(errno));
			close(server_fd);
			pthread_exit(NULL);
		}
		//make socket non-blocking
		fcntl(con[conSize], F_SETFL, O_NONBLOCK);

		printf("Server new connecton has been established [%s/%d]\n", inet_ntoa(caddr.sin_addr), caddr.sin_port);
		conSize++;
	}
	pthread_exit(NULL);
}

void* periodThread(void* arg) {
	
	while(!doneReading) {
        sleep(5);
		
		printf("---- Sensor 1 Durum: ----\n");
		readSensorValues(sensorler[0].ID);
		printf("\n");
		printf("---- Sensor 2 Durum: ----\n");
		readSensorValues(sensorler[1].ID);
		printf("\n");
		
    }

    return 0;
}

void serviceThread(void* arg) {
	int size;
	int client = 0;
	int ind = 0;
	int closed = 0;
	char msg[100];

	while (!closed) {
		for (int i = 0; i < conSize; i++) {
			//read
			if ((size = read(con[i], msg, sizeof(msg))) == -1) {
				printf("Error reading [%s] \n", strerror(errno));
			}
			else {
				msg[size] = '\0';
				printf("Read data [%s]\n", msg);
			}

			//provide services

			//reply to message

		}
	}
	
	for (int i = 0; i < conSize; i++) {
		close(con[i]);
	}
}

int main(void) {

	pthread_t t1, makeConnectionThread, serverServiceThread;

	system("sudo ./config.sh");

	sensorler[0].ID = 21;
	sensorler[1].ID = 20;

	// char *ip = "127.0.0.1";
	// char msg[100];

	//Server Socket Address
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(7777);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//Create server socket
	server_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		printf("Error on socket creation [%s] \n", strerror(errno));
		return (-1);
	}

	//Bind the address to server socket
	if (bind(server_fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr)) == -1) {
		printf("Error socket bind [%s] \n", strerror(errno));
		return (-1);
	}

	//Listen for a connection request
	if (listen(server_fd, MAX_CON)) {
		printf("Error socket listen [%s] \n", strerror(errno));
		return (-1);
	}

	//Create a thread which will accept connection requests
	pthread_create(&makeConnectionThread, NULL, makeConnection, NULL);



	int size;
	int client = 0;
	int ind = 0;
	int closed = 0;
	char msg[100];

	while (!closed) {
		for (int i = 0; i < conSize; i++) {
			//read
			if ((size = read(con[i], msg, sizeof(msg))) == -1) {
				printf("Error reading [%s] \n", strerror(errno));
			}
			else {
				msg[size] = '\0';
				printf("Read data [%s]\n", msg);
			}

			//provide services

			//reply to message

		}
	}
	
	for (int i = 0; i < conSize; i++) {
		close(con[i]);
	}



	// pthread_create(&t1, NULL, &periodThread, NULL);

	//read received messages and provides services
	// pthread_create(&serverServiceThread, NULL, &serviceThread, NULL);
	
	// pthread_join(serverServiceThread, NULL);
	// pthread_join(t1,NULL);

	//Close connections
	close(server_fd);

	return 0;
}

void readSensorValues(int port) {
	if (HIGH == GPIORead(port)) {
		printf("PORT: %d\n", port);
		printf("SENSOR ON\n");
		sensorler[0].state = 1;
	} else if(LOW == GPIORead(port)) {
		printf("PORT: %d\n", port);
		printf("SENSOR OFF\n");
		sensorler[0].state = 0;
	}
}