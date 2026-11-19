#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define MAX_DIM 10

int main() {
    int sock_fd;
    int n, i, j, a[MAX_DIM][MAX_DIM], type;
    char result[100];
    struct sockaddr_in server_addr;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr = (struct in_addr){ inet_addr(SERVER_IP) };

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to Matrix Server successfully.\n");
    printf("Enter the order of the matrix (max %d): ", MAX_DIM);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_DIM) {
        printf("Invalid dimension.\n");
        close(sock_fd);
        return 1;
    }

    srand(time(NULL));
    type = rand() % 4; // 0: Diagonal, 1: Upper Triangular, 2: Lower Triangular, 3: Normal

    printf("\nGenerated Random Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (type == 0) {
                a[i][j] = (i == j) ? (rand() % 50 + 1) : 0;
            } else if (type == 1) {
                a[i][j] = (i <= j) ? (rand() % 50 + 1) : 0;
            } else if (type == 2) {
                a[i][j] = (i >= j) ? (rand() % 50 + 1) : 0;
            } else {
                a[i][j] = rand() % 50 + 1;
            }
            printf("%4d ", a[i][j]);
        }
        printf("\n");
    }

    write(sock_fd, &n, sizeof(n));
    write(sock_fd, a, sizeof(a));

    read(sock_fd, result, sizeof(result));
    printf("\nServer Classification: %s\n", result);

    close(sock_fd);
    return 0;
}
