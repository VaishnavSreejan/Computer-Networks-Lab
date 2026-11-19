#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"

int main() {
    int sock_fd;
    int n;
    long fact = 0;
    struct sockaddr_in server_addr;

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

    // 3. Connect to server
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to Factorial Server successfully!\n");

    // 4. Input number
    printf("Enter a number to calculate factorial: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        close(sock_fd);
        return 1;
    }

    // 5. Send number to server
    write(sock_fd, &n, sizeof(n));

    // 6. Receive factorial from server
    read(sock_fd, &fact, sizeof(fact));
    printf("Factorial of %d = %ld\n", n, fact);

    // 7. Close socket
    close(sock_fd);
    return 0;
}
