# Experiment 3: Sentence Abbreviation Expander using UDP Socket

## Objective
To implement a connectionless client-server application using UDP sockets in C where the client sends a message containing abbreviations/internet slang, and the server replaces them with full English phrases and returns the translated sentence.

## Protocol & Architecture
- **Protocol**: UDP (Connectionless, datagram-based)
- **Socket Type**: `SOCK_DGRAM`
- **Default Port**: `8080`

## Supported Abbreviations
| Abbreviation | Expanded Meaning |
|--------------|------------------|
| `tbh` | to be honest |
| `ig` | I guess |
| `tbf` | to be fair |
| `atm` | at the moment |
| `irl` | in real life |
| `lol` | laughing out loud |
| `asap` | as soon as possible |
| `omg` | oh my god |
| `ttyl` | talk to you later |
| `idk` | I don't know |
| `nvm` | never mind |
| `btw` | by the way |

## Files
- `server.c`: Listens on UDP port 8080, parses incoming sentence, expands known abbreviations, and sends datagram back.
- `client.c`: Takes sentence input from user, sends UDP datagram to server, and displays translated sentence.

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
UDP Abbreviation Expander Server listening on port 8080...
Waiting for client datagram...
Received text: tbh idk what to do lol
Expanded text sent: to be honest I don't know what to do laughing out loud 
```

**Client:**
```text
Enter a sentence with abbreviations (e.g. 'tbh idk what to do lol asap'):
> tbh idk what to do lol

Translated Sentence:
to be honest I don't know what to do laughing out loud 
```
