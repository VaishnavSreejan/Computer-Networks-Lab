#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s, n;
    long fact;
    struct sockaddr_in server;

    s = socket(AF_INET, SOCK_STREAM, 0);

    if (s < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr =
        inet_addr("127.0.0.1");

    if (connect(s, (struct sockaddr *)&server,
                sizeof(server)) < 0)
    {
        perror("Connection failed");
        close(s);
        return 1;
    }

    printf("Connected to server successfully!\n");

    printf("Enter a number: ");
    scanf("%d", &n);

    write(s, &n, sizeof(n));

    read(s, &fact, sizeof(fact));

    printf("Factorial of %d = %ld\n", n, fact);

    close(s);

    return 0;
}