# Computer Networks Lab (B.Tech)

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Standard](https://img.shields.io/badge/Standard-POSIX%20Sockets-brightgreen.svg)](https://en.wikipedia.org/wiki/Berkeley_sockets)
[![Compiler](https://img.shields.io/badge/Compiler-GCC-orange.svg)](https://gcc.gnu.org/)
[![License](https://img.shields.io/badge/License-MIT-purple.svg)](LICENSE)

A curated collection of **Computer Networks Lab experiments** implemented in **C** using the **Berkeley Sockets API** for undergraduate engineering curriculum (B.Tech in Computer Science & Engineering).

---

## 📑 Table of Contents
- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Lab Experiments](#lab-experiments)
  - [1. TCP Factorial Server & Client](#1-tcp-factorial-server--client)
  - [2. TCP Matrix Classification Server & Client](#2-tcp-matrix-classification-server--client)
  - [3. UDP Abbreviation Expander Server & Client](#3-udp-abbreviation-expander-server--client)
  - [4. UDP Daytime / Time Server & Client](#4-udp-daytime--time-server--client)
  - [5. Multithreaded TCP Multi-Client Chat](#5-multithreaded-tcp-multi-client-chat)
- [Prerequisites & Tools](#prerequisites--tools)
- [General Compilation & Execution Guide](#general-compilation--execution-guide)
- [Socket Programming Overview](#socket-programming-overview)
- [Author](#author)

---

## 🔍 Overview

This repository demonstrates fundamental concepts in network programming:
- **Connection-oriented communication (TCP)** vs **Connectionless communication (UDP)**.
- Socket creation, endpoint binding, listening, connection acceptance, and graceful shutdown.
- Data serialization and structured data transfer (matrices, integers, formatted text).
- Real-time concurrent server architectures using **POSIX Threads (`pthread`)** and thread synchronization primitives (`pthread_mutex_t`).

---

## 📂 Repository Structure

```
Computer-Networks-Lab/
├── 01_TCP_Factorial/
│   ├── client.c                # TCP Factorial Client
│   ├── server.c                # TCP Factorial Server
│   └── README.md               # Experiment details & sample output
├── 02_TCP_Matrix_Classification/
│   ├── client.c                # Interactive Matrix Client (user input)
│   ├── server.c                # Matrix Type Classifier Server
│   ├── random_matrix_client.c  # Automated random matrix test client
│   └── README.md               # Experiment details & sample output
├── 03_UDP_Abbreviation_Expander/
│   ├── client.c                # UDP Abbreviation Client
│   ├── server.c                # UDP Text Expansion & Dictionary Server
│   └── README.md               # Experiment details & sample output
├── 04_UDP_Time_Server/
│   ├── client.c                # UDP Daytime Client (Time Request)
│   ├── server.c                # UDP Daytime Server (System Time)
│   └── README.md               # Experiment details & sample output
├── 05_TCP_MultiClient_Chat/
│   ├── client.c                # Multithreaded Chat Client
│   ├── server.c                # Multithreaded Broadcast Chat Server
│   └── README.md               # Experiment details & sample output
├── .gitignore                  # Git ignore rules for compiled binaries
└── README.md                   # Main documentation
```

---

## 🔬 Lab Experiments

### 1. TCP Factorial Server & Client
- **Folder**: [`01_TCP_Factorial`](01_TCP_Factorial/)
- **Protocol**: TCP (`SOCK_STREAM`)
- **Port**: `8080`
- **Description**: The client sends an integer to the server over a stream-oriented connection. The server computes the mathematical factorial of the number and replies with the computed value.

### 2. TCP Matrix Classification Server & Client
- **Folder**: [`02_TCP_Matrix_Classification`](02_TCP_Matrix_Classification/)
- **Protocol**: TCP (`SOCK_STREAM`)
- **Port**: `8080`
- **Description**: The client transmits the order and elements of a square matrix. The server analyzes the matrix structure and classifies it into:
  - **Diagonal Matrix** ($\forall i \ne j, A[i][j] = 0$)
  - **Upper Triangular Matrix** ($\forall i > j, A[i][j] = 0$)
  - **Lower Triangular Matrix** ($\forall i < j, A[i][j] = 0$)
  - **Normal Matrix** (otherwise)

### 3. UDP Abbreviation Expander Server & Client
- **Folder**: [`03_UDP_Abbreviation_Expander`](03_UDP_Abbreviation_Expander/)
- **Protocol**: UDP (`SOCK_DGRAM`)
- **Port**: `8080`
- **Description**: Demonstrates datagram socket communication. The client transmits sentences containing colloquial internet abbreviations (e.g., `tbh`, `idk`, `lol`, `asap`, `omg`). The server tokenizes the message, looks up each token in an abbreviation dictionary, expands matched terms, and sends back the translated message.

### 4. UDP Daytime / Time Server & Client
- **Folder**: [`04_UDP_Time_Server`](04_UDP_Time_Server/)
- **Protocol**: UDP (`SOCK_DGRAM`)
- **Port**: `8080`
- **Description**: Implements a network time query service over UDP. The client transmits a request packet to the server, and the server fetches its system timestamp via the standard C `<time.h>` library and sends back the formatted date and time string.

### 5. Multithreaded TCP Multi-Client Chat
- **Folder**: [`05_TCP_MultiClient_Chat`](05_TCP_MultiClient_Chat/)
- **Protocol**: TCP (`SOCK_STREAM`) with POSIX Threads (`pthread`)
- **Port**: `8080`
- **Description**: A concurrent group chat system. The server accepts multiple simultaneous client connections in an accept loop. Each connected client is serviced by a dedicated POSIX thread that reads incoming messages and broadcasts them to all other active clients with thread-safe client list management using mutex locks.

---

## 🛠️ Prerequisites & Tools

- **Operating System**: Linux (Ubuntu/Debian/Fedora), WSL (Windows Subsystem for Linux), or macOS.
- **Compiler**: GCC (GNU Compiler Collection) or Clang.
- **Libraries**:
  - Standard C Library (`libc`)
  - POSIX Threads Library (`libpthread`) for Experiment 5 (`-pthread` flag)

To install GCC on Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential
```

---

## 🚀 General Compilation & Execution Guide

For each experiment, open **two separate terminal windows** (one for the server and one for the client).

### Step 1: Run the Server First
```bash
cd <experiment_folder>
gcc server.c -o server
./server
```

### Step 2: Run the Client
```bash
cd <experiment_folder>
gcc client.c -o client
./client
```

> **Note for Experiment 5 (Multi-Client Chat)**: Compile with `-pthread`:
> ```bash
> gcc server.c -o server -pthread
> gcc client.c -o client -pthread
> ```
> You can open 3 or more terminals to run multiple `./client` instances and chat between them.

---

## 🌐 Socket Programming Overview

### TCP vs UDP Workflow

```
TCP (Connection-Oriented)                 UDP (Connectionless)
------------------------                 --------------------
 Server          Client                   Server          Client
   │               │                        │               │
socket()        socket()                 socket()        socket()
   │               │                        │               │
 bind()            │                      bind()            │
   │               │                        │               │
listen()           │                        │               │
   │               │                        │               │
accept() ◄──── connect()                    │               │
   │               │                        │               │
 read()  ◄────  write()                  recvfrom() ◄──  sendto()
   │               │                        │               │
 write() ────►   read()                   sendto()  ──► recvfrom()
   │               │                        │               │
close()         close()                  close()         close()
```

---

## 👤 Author

- **Vaishnav Sreejan**
- GitHub: [@VaishnavSreejan](https://github.com/VaishnavSreejan)
- Repository: [Computer-Networks-Lab](https://github.com/VaishnavSreejan/Computer-Networks-Lab.git)
