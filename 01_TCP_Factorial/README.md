# Experiment 1: Factorial Calculation using TCP Socket

## Objective
To implement a client-server application using TCP sockets in C where the client sends an integer to the server, and the server computes its factorial and returns the result.

## Protocol & Architecture
- **Protocol**: TCP (Connection-oriented, reliable)
- **Socket Type**: `SOCK_STREAM`
- **Default Port**: `8080`

## Files
- `server.c`: Listens on port 8080, accepts client connection, computes factorial of received number, and responds.
- `client.c`: Connects to server, prompts user for an integer, sends it to the server, and prints the returned factorial.

## Compilation & Execution

### 1. Compile
```bash
gcc server.c -o server
gcc client.c -o client
```

### 2. Run Server (Terminal 1)
```bash
./server
```

### 3. Run Client (Terminal 2)
```bash
./client
```

## Sample Output

**Server:**
```text
Factorial Server listening on port 8080...
Waiting for client connection...
Client connected successfully.
Received number: 5
Factorial of 5 is 120 (sent to client).
```

**Client:**
```text
Connected to Factorial Server successfully!
Enter a number to calculate factorial: 5
Factorial of 5 = 120
```

