#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>

int main() {

	int socket_fd;
	struct sockaddr_in caddr;
	char *ip = "192.168.2.41";
	char msg[100];

	//Socket Address
	caddr.sin_family = AF_INET;
	caddr.sin_port = htons(7777);
	if (inet_aton(ip, &caddr.sin_addr) == 0) {
		return (-1);
	}

	//Create socket
	socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1) {
		printf("Error on socket creation [%s] \n", strerror(errno));
		return (-1);
	}

	//Establish connection
	if (connect(socket_fd, (const struct sockaddr *)&caddr, sizeof(struct sockaddr)) == -1) {
		printf("Error on socket connect [%s] \n", strerror(errno));
		return (-1);
	}

	int closed = 0;

	//Read and write data
	while (!closed) {
		
		//got the keys pressed into a string until pressing #
        // printf("Enter a message: ");
        // scanf ("%[^\n]%*c", msg);

		//Send the command to the server
		if (write(socket_fd, msg, sizeof(msg)) != sizeof(msg)) {
			printf("Error writing [%s] \n", strerror(errno));
		}
		else {
			printf("Sent data [%s] \n", msg);
		}


		//read the reply message and print




	}
	
	//Close the connection
	close(socket_fd);
	return 0;

}
