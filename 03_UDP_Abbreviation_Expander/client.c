#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int sock_fd;
    char msg[BUFFER_SIZE];
    char result[BUFFER_SIZE * 2];
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

    // 3. Prompt user for input
    printf("Enter a sentence with abbreviations (e.g. 'tbh idk what to do lol asap'):\n> ");
    if (fgets(msg, sizeof(msg), stdin) == NULL) {
        close(sock_fd);
        return 0;
    }

    // 4. Send datagram to server
    sendto(sock_fd, msg, strlen(msg), 0, (struct sockaddr *)&server_addr, addr_len);

    // 5. Receive expanded sentence
    int n = recvfrom(sock_fd, result, sizeof(result) - 1, 0, (struct sockaddr *)&server_addr, &addr_len);
    if (n >= 0) {
        result[n] = '\0';
        printf("\nTranslated Sentence:\n%s\n", result);
    } else {
        perror("recvfrom failed");
    }

    close(sock_fd);
    return 0;
}
