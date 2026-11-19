#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s, c, n, i;
    long fact = 1;
    struct sockaddr_in server;

    s = socket(AF_INET, SOCK_STREAM, 0);

    if (s < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *)&server,
             sizeof(server)) < 0)
    {
        perror("Bind failed");
        close(s);
        return 1;
    }

    listen(s, 1);

    printf("Waiting for client...\n");

    c = accept(s, NULL, NULL);

    if (c < 0)
    {
        perror("Connection failed");
        close(s);
        return 1;
    }

    printf("Client connected\n");

    read(c, &n, sizeof(n));

    printf("Received number: %d\n", n);

    for (i = 1; i <= n; i++)
    {
        fact = fact * i;
    }

    write(c, &fact, sizeof(fact));

    printf("Factorial sent to client.\n");

    close(c);
    close(s);

    return 0;
}