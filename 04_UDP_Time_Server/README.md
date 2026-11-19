# Experiment 4: Date & Time Server using UDP Socket

## Objective
To implement a daytime service using UDP sockets in C where the client sends a time request to the server, and the server fetches its current system clock time and transmits it back to the client.

## Protocol & Architecture
- **Protocol**: UDP
- **Socket Type**: `SOCK_DGRAM`
- **Default Port**: `8080`

## Files
- `server.c`: Binds to UDP port 8080, reads incoming datagram request, formats system time with `ctime()`, and sends the string back.
- `client.c`: Transmits a "Time Request" packet to the server and prints the received date and time.

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
UDP Daytime Server listening on port 8080...
Waiting for client time requests...
Client Request Received: "Time Request"
Time sent to client: Thu Nov 19 20:05:00 2026
```

**Client:**
```text
Time request sent to server.
Current Server Date & Time: Thu Nov 19 20:05:00 2026
```
