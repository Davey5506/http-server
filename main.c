#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int init_socket(void);

int main(void){
	int socket_fd = init_socket();
	if(socket_fd < 0){
		perror("init_socket");
		exit(EXIT_FAILURE);
	}

	while(1){
		// client info
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);
		int *client_fd = malloc(sizeof(int));

		// accept client connection
		*client_fd = accept(socket_fd,
							(struct sockaddr *)&client_addr,
							&client_addr_len);
		if(*client_fd < 0){
			perror("accept failed");
			continue;
		}

		// create a new thread to handle client request
		pthread_t thread_id;
		pthread_create(&thread_id, NULL, NULL, (void*)client_fd);
		pthread_detach(thread_id);
	}
}

int init_socket(void){
	int socket_fd = -1;				// socket file descriptor
	struct sockaddr_in server_addr;	// socket config

	// create server socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0); // Initialize the socket
	if(socket_fd < 0){	// Check if initialization failed
		perror("socket failed");
		close(socket_fd);
		exit(EXIT_FAILURE);
	}

	// congif socket
	server_addr.sin_family = AF_INET;			// Set address type to IPv4
	server_addr.sin_addr.s_addr = INADDR_ANY;	// Set IP address
	server_addr.sin_port = htons(PORT);			// Set the port to bind the socket too

	// bind socket to port
	if(bind(socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
	/* Attempt to bind socket 
		and check for failure */
		perror("bind failed");
		close(socket_fd);
		exit(EXIT_FAILURE);
	}

	// Listen for connections
	if(listen(socket_fd, 10) < 0){ /* Listen for traffic
									  and check for failure. */
		perror("listen failed");
		close(socket_fd);
		exit(EXIT_FAILURE);
	}
	return socket_fd;
}
