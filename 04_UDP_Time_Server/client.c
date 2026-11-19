#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 256

int main() {
    int sock_fd;
    char msg[BUFFER_SIZE] = "Time Request";
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    // 1. Create UDP socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 3. Send time request
    sendto(sock_fd, msg, strlen(msg) + 1, 0, (struct sockaddr *)&server_addr, addr_len);
    printf("Time request sent to server.\n");

    // 4. Receive current time from server
    int n = recvfrom(sock_fd, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&server_addr, &addr_len);
    if (n >= 0) {
        msg[n] = '\0';
        printf("Current Server Date & Time: %s", msg);
    } else {
        perror("recvfrom failed");
    }

    close(sock_fd);
    return 0;
}
