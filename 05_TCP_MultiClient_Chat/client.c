#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 256

int sock_fd;

void *receive_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = recv(sock_fd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        printf("[Friend]: %s", buffer);
        fflush(stdout);
    }
    return NULL;
}

int main() {
    struct sockaddr_in server_addr;
    pthread_t recv_thread;
    char buffer[BUFFER_SIZE];

    // 1. Create TCP socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 3. Connect to chat server
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to chat server failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("=========================================\n");
    printf(" Connected to Multi-Client Chat Server!  \n");
    printf(" Type your messages and press Enter.     \n");
    printf(" Type 'exit' to disconnect.              \n");
    printf("=========================================\n\n");

    // 4. Start background receiving thread
    if (pthread_create(&recv_thread, NULL, receive_messages, NULL) != 0) {
        perror("Failed to create receiving thread");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // 5. Send message loop
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        if (strncmp(buffer, "exit", 4) == 0 && (buffer[4] == '\n' || buffer[4] == '\0')) {
            printf("Disconnecting from chat...\n");
            break;
        }

        send(sock_fd, buffer, strlen(buffer), 0);
    }

    close(sock_fd);
    return 0;
}
