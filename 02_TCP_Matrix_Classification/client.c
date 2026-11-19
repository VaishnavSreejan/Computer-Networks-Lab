#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define MAX_DIM 10

int main() {
    int sock_fd;
    int n, a[MAX_DIM][MAX_DIM], i, j;
    char result[100];
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
        perror("Connection failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to Matrix Server successfully!\n");

    // 4. Input matrix dimensions and elements
    printf("Enter the order of the square matrix (max %d): ", MAX_DIM);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_DIM) {
        printf("Invalid matrix dimension.\n");
        close(sock_fd);
        return 1;
    }

    printf("Enter elements of the %d x %d matrix:\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 5. Send order and matrix to server
    write(sock_fd, &n, sizeof(n));
    write(sock_fd, a, sizeof(a));

    // 6. Receive classification result
    read(sock_fd, result, sizeof(result));
    printf("\nResult from Server: The given matrix is a \"%s\"\n", result);

    close(sock_fd);
    return 0;
}
