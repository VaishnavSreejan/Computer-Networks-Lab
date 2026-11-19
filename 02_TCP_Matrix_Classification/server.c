#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define MAX_DIM 10

int main() {
    int server_fd, client_fd;
    int n, a[MAX_DIM][MAX_DIM], i, j;
    int upper = 1, lower = 1, diagonal = 1;
    char result[100];
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

    // 3. Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Matrix Classification Server listening on port %d...\n", PORT);
    printf("Waiting for client connection...\n");

    // 5. Accept connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Client connected successfully.\n");

    // 6. Read matrix order and elements
    read(client_fd, &n, sizeof(n));
    read(client_fd, a, sizeof(a));

    printf("\nReceived Matrix of order %d x %d:\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%4d ", a[i][j]);
        }
        printf("\n");
    }

    // 7. Determine matrix type
    upper = 1;
    lower = 1;
    diagonal = 1;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i > j && a[i][j] != 0)
                upper = 0;   // elements below main diagonal must be 0 for upper triangular
            if (i < j && a[i][j] != 0)
                lower = 0;   // elements above main diagonal must be 0 for lower triangular
            if (i != j && a[i][j] != 0)
                diagonal = 0;// off-diagonal elements must be 0 for diagonal
        }
    }

    if (diagonal)
        strcpy(result, "Diagonal Matrix");
    else if (upper)
        strcpy(result, "Upper Triangular Matrix");
    else if (lower)
        strcpy(result, "Lower Triangular Matrix");
    else
        strcpy(result, "Normal Matrix");

    // 8. Send result to client
    write(client_fd, result, sizeof(result));
    printf("Matrix Classification Result: %s (sent to client)\n", result);

    close(client_fd);
    close(server_fd);
    return 0;
}
