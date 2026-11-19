# Experiment 2: Matrix Type Determination using TCP Socket

## Objective
To develop a client-server socket program in C where the client transmits a square matrix to the server, and the server evaluates whether the matrix is:
1. **Diagonal Matrix**: All non-diagonal elements are 0.
2. **Upper Triangular Matrix**: All elements below the main diagonal are 0.
3. **Lower Triangular Matrix**: All elements above the main diagonal are 0.
4. **Normal Matrix**: None of the above special conditions are met.

## Protocol & Architecture
- **Protocol**: TCP
- **Socket Type**: `SOCK_STREAM`
- **Default Port**: `8080`

## Files
- `server.c`: Receives the matrix dimension and elements, analyzes matrix properties, and sends the classification result back.
- `client.c`: Prompts the user to enter matrix order and elements, sends data to the server, and displays the result.
- `random_matrix_client.c`: An automated test client that generates a random square matrix of a chosen type and validates server response.

## Compilation & Execution

### 1. Compile
```bash
gcc server.c -o server
gcc client.c -o client
gcc random_matrix_client.c -o random_client
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
Matrix Classification Server listening on port 8080...
Waiting for client connection...
Client connected successfully.

Received Matrix of order 3 x 3:
   5    0    0 
   0    8    0 
   0    0    3 
Matrix Classification Result: Diagonal Matrix (sent to client)
```

**Client:**
```text
Connected to Matrix Server successfully!
Enter the order of the square matrix (max 10): 3
Enter elements of the 3 x 3 matrix:
5 0 0
0 8 0
0 0 3

Result from Server: The given matrix is a "Diagonal Matrix"
```
