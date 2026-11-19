# Computer Networks Lab (B.Tech)

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Standard](https://img.shields.io/badge/Standard-POSIX%20Sockets-brightgreen.svg)](https://en.wikipedia.org/wiki/Berkeley_sockets)
[![Compiler](https://img.shields.io/badge/Compiler-GCC-orange.svg)](https://gcc.gnu.org/)

B.Tech Computer Networks Lab experiments implemented in C using socket programming (TCP/UDP).

---

## 📑 Table of Contents
- [Repository Structure](#-repository-structure)
- [Lab Experiments](#-lab-experiments)
  - [1. TCP Factorial Server & Client](#1-tcp-factorial-server--client)
  - [2. TCP Matrix Classification Server & Client](#2-tcp-matrix-classification-server--client)
  - [3. UDP Abbreviation Expander Server & Client](#3-udp-abbreviation-expander-server--client)
  - [4. UDP Daytime / Time Server & Client](#4-udp-daytime--time-server--client)
  - [5. Multithreaded TCP Multi-Client Chat](#5-multithreaded-tcp-multi-client-chat)
- [Compilation & Execution](#-compilation--execution)
- [Author](#-author)

---

## 📂 Repository Structure

```
Computer-Networks-Lab/
├── 01_TCP_Factorial/
│   ├── factorialclient.c       # Factorial Client
│   ├── factorialserver.c       # Factorial Server
│   ├── factclient.c            # Alternate client variant
│   ├── factserver.c            # Alternate server variant
│   ├── client.c                # (Copy of factorialclient.c)
│   ├── server.c                # (Copy of factorialserver.c)
│   └── README.md
│
├── 02_TCP_Matrix_Classification/
│   ├── matrixclient.c          # Matrix Client
│   ├── matrixserver.c          # Matrix Server (determines type)
│   ├── matclient.c             # Alternate client variant
│   ├── matserver.c             # Alternate server variant
│   ├── mclient.c               # Matrix client with random generation
│   ├── mserver.c               # Matrix server with random generation
│   ├── client.c                # (Copy of matrixclient.c)
│   ├── server.c                # (Copy of matrixserver.c)
│   └── README.md
│
├── 03_UDP_Abbreviation_Expander/
│   ├── meaningclient.c         # Sentence translation client
│   ├── meaningserver.c         # Abbreviation lookup server
│   ├── abbclient.c             # Abbreviation client variant
│   ├── abbserver.c             # Abbreviation server variant
│   ├── abbrclient.c            # Abbreviation client variant
│   ├── abbrserver.c            # Abbreviation server variant
│   ├── client.c                # (Copy of meaningclient.c)
│   ├── server.c                # (Copy of meaningserver.c)
│   └── README.md
│
├── 04_UDP_Time_Server/
│   ├── timeclient.c            # UDP Time Client
│   ├── timeserver.c            # UDP Time Server
│   ├── tclient.c               # Alternate time client
│   ├── tserver.c               # Alternate time server
│   ├── client.c                # (Copy of timeclient.c)
│   ├── server.c                # (Copy of timeserver.c)
│   └── README.md
│
├── 05_TCP_MultiClient_Chat/
│   ├── multiclient.c           # Multithreaded Chat Client
│   ├── multiserver.c           # Multithreaded Chat Server
│   ├── mulclient.c             # Alternate multichat client
│   ├── mulserver.c             # Alternate multichat server
│   ├── mullcli.c               # Alternate client variant
│   ├── mullser.c               # Alternate server variant
│   ├── client.c                # (Copy of multiclient.c)
│   ├── server.c                # (Copy of multiserver.c)
│   └── README.md
│
├── .gitignore
└── README.md
```

---

## 🔬 Lab Experiments

### 1. TCP Factorial Server & Client
- **Folder**: `01_TCP_Factorial`
- **Protocol**: TCP (`SOCK_STREAM`)
- **Port**: `8080`
- **Description**: Client sends an integer number to the server. The server calculates the factorial and sends the result back to the client.

### 2. TCP Matrix Classification Server & Client
- **Folder**: `02_TCP_Matrix_Classification`
- **Protocol**: TCP (`SOCK_STREAM`)
- **Port**: `8080`
- **Description**: Client sends the matrix order and elements to the server. The server checks whether the matrix is a **Diagonal Matrix**, **Upper Triangular Matrix**, **Lower Triangular Matrix**, or **Normal Matrix**, and returns the result.

### 3. UDP Abbreviation Expander Server & Client
- **Folder**: `03_UDP_Abbreviation_Expander`
- **Protocol**: UDP (`SOCK_DGRAM`)
- **Port**: `8080` / `9002`
- **Description**: Client sends a sentence with abbreviations (such as `tbh`, `idk`, `lol`, `omg`, `asap`). The server translates the abbreviations to their full meanings and sends back the expanded sentence.

### 4. UDP Daytime / Time Server & Client
- **Folder**: `04_UDP_Time_Server`
- **Protocol**: UDP (`SOCK_DGRAM`)
- **Port**: `8080`
- **Description**: Client sends a time request message to the server. The server reads the current system time using `time.h` and returns the formatted time string to the client.

### 5. Multithreaded TCP Multi-Client Chat
- **Folder**: `05_TCP_MultiClient_Chat`
- **Protocol**: TCP (`SOCK_STREAM`) with `pthread`
- **Port**: `8080`
- **Description**: Multiple clients connect to the server concurrently. The server creates a separate thread for each client and broadcasts any incoming message to all other connected clients.

---

## 🚀 Compilation & Execution

Open two terminal windows:

### For TCP Programs (e.g. Factorial)
```bash
# Terminal 1 - Server
cd 01_TCP_Factorial
gcc factorialserver.c -o server
./server

# Terminal 2 - Client
cd 01_TCP_Factorial
gcc factorialclient.c -o client
./client
```

### For UDP Programs (e.g. Time Server)
```bash
# Terminal 1 - Server
cd 04_UDP_Time_Server
gcc timeserver.c -o server
./server

# Terminal 2 - Client
cd 04_UDP_Time_Server
gcc timeclient.c -o client
./client
```

### For Multi-Client Chat (Link with `-pthread`)
```bash
# Terminal 1 - Server
cd 05_TCP_MultiClient_Chat
gcc multiserver.c -o server -pthread
./server

# Terminal 2 - Client 1
cd 05_TCP_MultiClient_Chat
gcc multiclient.c -o client -pthread
./client

# Terminal 3 - Client 2
cd 05_TCP_MultiClient_Chat
gcc multiclient.c -o client -pthread
./client
```

---

## 👤 Author

- **Vaishnav Sreejan**
- GitHub: [@VaishnavSreejan](https://github.com/VaishnavSreejan)
- Repository: [Computer-Networks-Lab](https://github.com/VaishnavSreejan/Computer-Networks-Lab.git)
