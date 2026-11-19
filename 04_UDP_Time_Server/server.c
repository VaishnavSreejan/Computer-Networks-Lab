#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 256

int main() {
    int sock_fd;
    char msg[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    time_t current_time;

    // 1. Create UDP socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind socket
    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Daytime Server listening on port %d...\n", PORT);
    printf("Waiting for client time requests...\n");

    // 4. Receive request from client
    int n = recvfrom(sock_fd, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&client_addr, &addr_len);
    if (n >= 0) {
        msg[n] = '\0';
        printf("Client Request Received: \"%s\"\n", msg);

        // 5. Get current system time
        time(&current_time);
        char *time_str = ctime(&current_time);
        strncpy(msg, time_str, sizeof(msg) - 1);
        msg[sizeof(msg) - 1] = '\0';

        // 6. Send time string back to client
        sendto(sock_fd, msg, strlen(msg) + 1, 0, (struct sockaddr *)&client_addr, addr_len);
        printf("Time sent to client: %s", msg);
    }

    close(sock_fd);
    return 0;
}
