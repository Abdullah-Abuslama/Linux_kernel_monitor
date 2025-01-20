# Linux Kernel Monitor

A real-time kernel monitoring system that provides insights into Linux kernel internals through a custom kernel module and user-space visualization interface.

## Overview

This project consists of two main components:
- A Linux kernel module that collects system statistics (CPU, memory, process data)
- A user-space application that presents the data in a terminal-based UI using ncurses

![Linux Kernel Monitor](https://raw.githubusercontent.com/Abdullah-Abuslama/Linux_kernel_monitor/main/docs/screenshot.png)

## Features

- Real-time system statistics monitoring
- Memory usage tracking and visualization
- Process count monitoring
- CPU utilization metrics
- Interactive terminal-based user interface

## Prerequisites

- Ubuntu 24.04 or compatible Linux distribution
- Build essentials and kernel headers
- NCurses library

```bash
sudo apt-get update
sudo apt-get install build-essential linux-headers-$(uname -r) libncurses5-dev
```

## Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/linux-kernel-monitor.git
cd linux-kernel-monitor
```

2. Build the kernel module and user application:
```bash
make
```

## Usage

1. Load the kernel module:
```bash
sudo insmod Kernel_Module.ko
```

2. Run the monitoring application:
```bash
sudo ./monitor
```

3. When finished, unload the module:
```bash
sudo rmmod Kernel_Module
```

## Project Structure

```
linux-kernel-monitor/
├── src/
│   ├── Kernel_Module.c
│   └── User_Space_Application.c
├── docs/
│   └── screenshot.png
├── Makefile
├── README.md
└── LICENSE
```

## Technical Details

The kernel module creates a proc file at `/proc/kernel_monitor` that exports system statistics. The user-space application reads this data and presents it through an ncurses interface.

### Kernel Module
- Collects system statistics using kernel APIs
- Exports data through procfs
- Minimal performance impact

### User Interface
- Built with NCurses for terminal-based visualization
- Real-time updates
- Clear, organized display of system metrics

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the Apache 2.0 License - see the [LICENSE](LICENSE) file for details.

## Authors

- Your Name (@Abdullah-Abuslama)

## Acknowledgments

- Linux Kernel Documentation
- NCurses Library Documentation
