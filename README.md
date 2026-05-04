# 🧰 Linux CLI Tools Collection (C)

## 📖 Overview

This repository contains a collection of custom Linux command-line tools written in **C**, designed to enhance productivity, automation, and system interaction directly from the terminal.

Each tool is implemented as a standalone CLI command and can be installed system-wide, allowing seamless usage like any native Linux command.

---

## 🎯 Purpose

The goal of this project is to:

* Build practical and efficient CLI tools in C
* Explore low-level system programming on Linux
* Practice software engineering concepts (modularity, packaging, automation)
* Provide real-world tools usable in everyday workflows

---

## ⚙️ Features

* 🔹 Multiple custom CLI commands
* 🔹 Written in pure C (with external libraries when needed)
* 🔹 Built using **CMake**
* 🔹 Packaged as **.deb** using CPack
* 🔹 Easy installation via `dpkg`
* 🔹 Designed for Linux environments (WSL compatible)

---

## 📦 Installation

### 1. Build and package

```bash
./build.sh
```

### 2. Install the package

```bash
sudo dpkg -i pkg/*.deb
```

### 3. Run commands

```bash
weather
```

---

## 🛠️ Project Structure

```
.
├── src/            # Source code for CLI tools
├── build/          # Build directory (generated)
├── pkg/            # Generated .deb packages
├── CMakeLists.txt  # Build configuration
└── startup.sh
```

---

## 🚀 Example Tool

### `weather`

Displays the current date and weather information directly in the terminal.

```bash
weather
weather Paris
weather --json
```

---

## 🧠 Technologies Used

* C (C99)
* CMake
* CPack (Debian packaging)
* libcurl (HTTP requests)
* json-c (JSON parsing)

---

## 🔮 Future Improvements

* Add more CLI tools (system monitoring, networking, automation)
* Improve argument parsing (`getopt`)
* Add colored terminal output
* Implement caching mechanisms
* Create a custom APT repository
* CI/CD pipeline for automated builds and releases

---

## 👨‍💻 Author

**Oussama Dbibih**
Embedded Systems & Software Engineer

---

## 📄 License

This project is open-source and available under the GNU License.
