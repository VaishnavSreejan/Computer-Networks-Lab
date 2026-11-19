# Experiment 5: Multi-Client Chat Server using TCP & Multithreading (pthread)

## Objective
To build a concurrent multi-client group chat application using TCP sockets and POSIX threads (`pthread`) in C. The server accepts multiple simultaneous client connections and broadcasts incoming messages from any client to all other connected clients in real time.

## Protocol & Architecture
- **Protocol**: TCP
- **Concurrency Model**: Multithreaded server (one thread per client connection, protected by mutex locks)
- **Socket Type**: `SOCK_STREAM`
- **Default Port**: `8080`

## Files
- `server.c`: Accepts multiple client connections, creates a worker thread for each client, and broadcasts messages to other participants.
- `client.c`: Spawns a background thread to receive and display messages while the main thread takes user input from the console.

## Compilation & Execution

### 1. Compile (Link with `-pthread`)
```bash
gcc server.c -o server -pthread
gcc client.c -o client -pthread
```

### 2. Run Server (Terminal 1)
```bash
./server
```

### 3. Run Client 1 (Terminal 2)
```bash
./client
```

### 4. Run Client 2 (Terminal 3)
```bash
./client
```

## Sample Output

**Server:**
```text
Multi-Client Chat Server listening on port 8080...
Waiting for clients to join...
New client connected. Active clients: 1
New client connected. Active clients: 2
[Broadcast] Hello from Client 1!
[Broadcast] Hey there, Client 2 here!
```

**Client 1:**
```text
=========================================
 Connected to Multi-Client Chat Server!  
 Type your messages and press Enter.     
 Type 'exit' to disconnect.              
=========================================

Hello from Client 1!
[Friend]: Hey there, Client 2 here!
```

**Client 2:**
```text
=========================================
 Connected to Multi-Client Chat Server!  
 Type your messages and press Enter.     
 Type 'exit' to disconnect.              
=========================================

[Friend]: Hello from Client 1!
Hey there, Client 2 here!
```
