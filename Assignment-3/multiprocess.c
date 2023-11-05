#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Include Socket Programming Library
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


unsigned int factArr[21]; // Factorial Array

// Network Constants
const char* PORT = "8081";



void calcFactArr() {
    factArr[0] = 1;
    for (int i = 1; i < 21; i++) {
        factArr[i] = factArr[i - 1] * i;
    }
}

unsigned int fact(int n) {
    if(n < 0) n = 0;
    if(n > 20) n = 20;
    return factArr[n];
}

int main() {
    calcFactArr(); // Calculate Factorial Array

    // Socket Programming : Server
    // Fill the information about the server
    int status;
    struct addrinfo hints, *servinfo, *p;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((status = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		printf("getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

    // Create a socket
    int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if(sockfd == -1) {
        printf("Error in creating socket\n");
        return 1;
    }

    // Bind the socket to the IP and PORT
    status = bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
    if(status == -1) {
        printf("Error in binding socket\n");
        return 1;
    }

    // Listen for connections
    status = listen(sockfd, 10);
    if(status == -1) {
        printf("Error in listening\n");
        return 1;
    }
    printf("Listening for connections\n");
    // Accept a connection
    struct sockaddr_storage client_addr;
    socklen_t client_addr_size = sizeof client_addr;
    while(true){

        int new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_size);
        if(new_fd == -1) {
            printf("Error in accepting connection\n");
            return 1;
        }
        // printf("Connection accepted\n");

        // Receive data from client
        if(!fork()){
            close(sockfd); // Child doesn't need the listener
            // printf("Child process created\n");
            while(true){
                unsigned int n;
                status = recv(new_fd, &n, sizeof n, 0);
                if(status == -1) {
                    printf("Error in receiving data\n");
                    exit(0);
                }
                
                // Calculate factorial
                unsigned int fact_n = fact(n);

                printf("Factorial of %u is %u\n", n, fact_n);

                // Send data to client
                status = send(new_fd, &fact_n, sizeof fact_n, 0);
                if(status == -1) {
                    printf("Error in sending data\n");
                    exit(0);
                }

            }
            close(new_fd);
            exit(0);
        }
        // printf("Connection closed\n");
    }
    // Close the socket
    // close(new_fd);
    // close(sockfd);




    //

    // Bind Socket to IP:PORT
    // inet_pton(AF_INET, ""

    return 0;
}
