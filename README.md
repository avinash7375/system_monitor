# System Monitor

## Overview
The **System Monitor** is a C-based application that tracks real-time system metrics such as CPU usage, memory usage, disk usage, CPU temperature, and system uptime.

## Features
- Displays CPU, memory, swap, and disk usage
- Monitors CPU temperature
- Shows system uptime
- Updates in real-time

## Project Structure
```
system-monitor/
├── include/
│   ├── metrics.h
│   ├── display.h
├── src/
│   ├── metrics.c
│   ├── display.c
│   ├── main.c
└── Makefile
```

## Prerequisites
Ensure you have the following installed:
- **GCC (GNU Compiler Collection)**
- **Make** (build automation tool)
- **Linux system** (supports `/proc/stat`, `/sys/class/thermal`)

## Installation & Running

### 1. Clone the Repository
```sh
git clone https://github.com/avinash7375/system_monitor.git
cd system_monitor
```

### 2. Build the Project
```sh
make
```

### 3. Run the System Monitor
```sh
./system-monitor
```

### 4. Clean Up (Optional)
To remove the compiled files:
```sh
make clean
```

## Usage
- The system monitor updates every **2 seconds**.
- Press **Ctrl+C** to exit the program.

## Contributing
Feel free to fork the repository and submit pull requests for improvements!

