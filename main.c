#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int init_socket(void);

int main(void){
	init_socket();
}

int init_socket(void){
	int socket_fd;					// socket file descriptor
	struct sockaddr_in server_addr;	// socket config

	// create server socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0); // Initialize the socket
	if(socket_fd < 0){	// Check if initialization failed
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// congif socket
	server_addr.sin_family = AF_INET;			// Set address type to IPv4
	server_addr.sin_addr.s_addr = INADDR_ANY;	// Set IP address
	server_addr.sin_port = htons(PORT);			// Set the port to bind the socket too

	// bind socket to port
	if(bind(socket_fd, &server_addr, sizeof(server_addr)) < 0){ /* Attempt to bind socket 
																	and check for failure */
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// Listen for connections
	if(listen(socket_fd, 10) < 0){ /* Listen for traffic
									  and check for failure. */
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
}
