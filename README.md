# 🖥️ RISC-V Operating System

A simple yet functional educational operating system written in **C** and **C++**, targeting the **RISC-V** architecture. This OS demonstrates essential systems programming concepts like memory management, threading, synchronization, and I/O. Done as part of the coursework for the course Operating Systems 1.

## ✨ Features

- 🗃️ **Memory Allocator**  
  Custom dynamic memory management for runtime allocation and deallocation.

- 🔄 **Context Switching**  
  Low-level support for switching between thread execution contexts.

- 🧵 **Thread Management**  
  Lightweight thread creation, scheduling, and termination.

- 🔐 **Semaphores**  
  Counting semaphores for safe inter-thread synchronization.

- 🖥️ **Input/Output**  
  Basic character-level console input and output.

## 🏗️ Architecture

- **Target Platform:** RISC-V 🦾  
- **Languages Used:** C and C++ 💻  

## 🛠️ Building

Ensure a RISC-V GCC toolchain is installed.

## 📁 Project Structure
  - src/ – Kernel and subsystem source files
  - include/ – Header files
  - Makefile – Build configuration

## 🎯 Extensions
This project serves as a foundation for learning low-level OS development. Potential future extensions include:
  - Filesystems
  - Device drivers
  - Smarter schedulers
