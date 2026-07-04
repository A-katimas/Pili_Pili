*This project has been created as part of the 42 curriculum by jtardieu*

# 🏃‍♂️ Codexion

<table>
  <tr>
    <td>
      <img src="https://media1.tenor.com/m/99ovDICLZvsAAAAd/interesting-hmm.gif">
    </td>
    <td align="center">
      <h2>Master the race for resources before the deadline masters you</h2>
    </td>
  </tr>
</table>

# Description

**Codexion** is a thrilling concurrency challenge where multiple coders compete for limited USB dongles in a shared quantum coding hub.

Think of it like this: 🎯
- 4️⃣ coders, all desperately wanting to compile
- 4️⃣ USB dongles
- ⏰ A race against time before BURNOUT 🔥

Master **thread synchronization**, avoid **deadlocks**, and keep everyone from going insane!

## 🚀 Quick Start

```bash
make
./codexion 4 800 200 200 100 5 50 edf
```

## ⚙️ How to Run

| Command | What it does |
|---------|-------------|
| `make` | 🏗️ Compile the project |
| `make clean` | 🧹 Remove object files |
| `make fclean` | 🗑️ Remove everything (including binary) |
| `make re` | 🔄 Rebuild from scratch |

## 📋 Parameters Explained

```bash
./codexion <coders> <burnout> <compile> <debug> <refactor> <required> <cooldown> <scheduler>
```

| Parameter | Example | What it means |
|-----------|---------|---------------|
| `coders` | 4 | Number of coders competing |
| `burnout` | 800 | Milliseconds before a coder melts down 🔥 |
| `compile` | 200 | Time to compile (ms) |
| `debug` | 200 | Time to debug (ms) |
| `refactor` | 100 | Time to refactor (ms) |
| `required` | 5 | Compiles each coder needs to do |
| `cooldown` | 50 | Dongle recovery time (ms) |
| `scheduler` | `fifo` or `edf` | Who gets the dongle first? |

## 🎮 Example Runs

### 🔥 Easy Mode
```bash
./codexion 2 2000 200 100 100 3 50 fifo
```

### 😰 Medium Mode
```bash
./codexion 4 800 200 200 100 5 50 edf
```

### 💀 Hard Mode
```bash
./codexion 8 400 200 200 100 10 100 edf
```

## 🧵 Threading Architecture

| Component | Job |
|-----------|-----|
| 🧑‍💻 **Coder Threads** | Compete for dongles, compile, debug, refactor |
| 🎛️ **Monitor Thread** | Watches for burnouts & completion |
| 🔐 **Mutexes** | Protects shared dongle state |
| 🔔 **Condition Variables** | Efficient thread wake-ups |

## 🎯 Key Concepts Implemented

### ✅ Deadlock Prevention
- **Lock Ordering** 🔑: Always grab dongles in ascending ID order