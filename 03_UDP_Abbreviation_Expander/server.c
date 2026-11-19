#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock_fd;
    char msg[BUFFER_SIZE];
    char result[BUFFER_SIZE * 2] = "";
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Abbreviation dictionary
    const char *abbr[] = {
        "tbh", "ig", "tbf", "atm", "irl",
        "lol", "asap", "omg", "ttyl", "idk",
        "nvm", "btw"
    };

    const char *meaning[] = {
        "to be honest", "I guess", "to be fair", "at the moment", "in real life",
        "laughing out loud", "as soon as possible", "oh my god", "talk to you later", "I don't know",
        "never mind", "by the way"
    };
    int dict_size = sizeof(abbr) / sizeof(abbr[0]);

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

    printf("UDP Abbreviation Expander Server listening on port %d...\n", PORT);
    printf("Waiting for client datagram...\n");

    // 4. Receive message from client
    int n = recvfrom(sock_fd, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&client_addr, &addr_len);
    if (n < 0) {
        perror("recvfrom failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    msg[n] = '\0';
    printf("Received text: %s\n", msg);

    // 5. Expand abbreviations
    char *word = strtok(msg, " ,.!?\n\r");
    while (word != NULL) {
        int found = 0;
        for (int i = 0; i < dict_size; i++) {
            if (strcasecmp(word, abbr[i]) == 0) {
                strcat(result, meaning[i]);
                found = 1;
                break;
            }
        }
        if (!found) {
            strcat(result, word);
        }
        strcat(result, " ");
        word = strtok(NULL, " ,.!?\n\r");
    }

    // 6. Send expanded result back to client
    sendto(sock_fd, result, strlen(result), 0, (struct sockaddr *)&client_addr, addr_len);
    printf("Expanded text sent: %s\n", result);

    close(sock_fd);
    return 0;
}
