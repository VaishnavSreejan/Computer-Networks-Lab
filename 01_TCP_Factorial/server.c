#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int server_fd, client_fd;
    int n, i;
    long fact = 1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // 1. Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind socket to IP/Port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Factorial Server listening on port %d...\n", PORT);
    printf("Waiting for client connection...\n");

    // 5. Accept client connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Client connected successfully.\n");

    // 6. Read number from client
    read(client_fd, &n, sizeof(n));
    printf("Received number: %d\n", n);

    // 7. Calculate factorial
    fact = 1;
    for (i = 1; i <= n; i++) {
        fact *= i;
    }

    // 8. Send result back to client
    write(client_fd, &fact, sizeof(fact));
    printf("Factorial of %d is %ld (sent to client).\n", n, fact);

    // 9. Close sockets
    close(client_fd);
    close(server_fd);
    return 0;
}
